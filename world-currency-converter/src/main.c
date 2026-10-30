/* ============================================================================
 *  WORLD CURRENCY CONVERTER
 *  ----------------------------------------------------------------------------
 *  A terminal currency converter written in portable C (C99).
 *  Uses a dated SNAPSHOT of real exchange rates stored in rates.h - no internet needed.
 *
 *  C concepts demonstrated
 *      - switch     : main menu, region names / colours, region filter
 *      - functions  : small single-purpose functions, one per feature
 *      - arrays     : currency table, history ring buffer, text buffers
 *      - arithmetic : cross-rate conversion through a USD base
 *
 *  Conversion formula (every rate is "units per 1 USD"):
 *      result = amount / rate_from * rate_to
 * ========================================================================== */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#ifdef _WIN32
#include <windows.h>
#endif

#include "rates.h"

/* ------------------------------ Look & feel ------------------------------- */
#define RESET   "\033[0m"
#define BOLD    "\033[1m"
#define DIM     "\033[2m"
#define RED     "\033[91m"
#define GREEN   "\033[92m"
#define YELLOW  "\033[93m"
#define BLUE    "\033[94m"
#define MAGENTA "\033[95m"
#define CYAN    "\033[96m"
#define WHITE   "\033[97m"

#define BOX_WIDTH    62
#define PAGE_SIZE    16
#define HISTORY_MAX  8
#define MAX_AMOUNT   1e12

/* ------------------------------ Global state ------------------------------ */
static double default_rate[CURRENCY_COUNT];   /* untouched copy of rates.h    */

typedef struct {                              /* one finished conversion      */
    char   from[4];
    char   to[4];
    double amount;
    double result;
} HistoryItem;

static HistoryItem history[HISTORY_MAX];      /* ring buffer of recent items  */
static int history_count = 0;
static int history_next  = 0;

/* =========================== Terminal utilities =========================== */

static void setup_terminal(void)
{
#ifdef _WIN32
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD mode = 0;
    SetConsoleOutputCP(65001);                       /* UTF-8 box characters  */
    if (GetConsoleMode(h, &mode))
        SetConsoleMode(h, mode | 0x0004);            /* ENABLE_VT_PROCESSING  */
#endif
}

static void clear_screen(void)
{
    printf("\033[2J\033[H");
}

static void repeat(const char *s, int n)
{
    for (int i = 0; i < n; i++) fputs(s, stdout);
}

/* Reads one line and trims it. Exits cleanly on end-of-input (Ctrl+D/Ctrl+Z). */
static void read_line(const char *prompt, char *buf, size_t size)
{
    fputs(prompt, stdout);
    fflush(stdout);
    if (!fgets(buf, (int)size, stdin)) {
        printf("\n" RESET "  Goodbye!\n");
        exit(0);
    }
    buf[strcspn(buf, "\r\n")] = '\0';

    size_t start = 0, len = strlen(buf);
    while (buf[start] && isspace((unsigned char)buf[start])) start++;
    while (len > start && isspace((unsigned char)buf[len - 1])) len--;
    memmove(buf, buf + start, len - start);
    buf[len - start] = '\0';
}

static void pause_for_enter(void)
{
    char tmp[16];
    read_line(DIM "\n  Press Enter to continue..." RESET, tmp, sizeof tmp);
}

/* Case-insensitive helpers (strcasecmp is not available everywhere). */
static int ci_equal(const char *a, const char *b)
{
    while (*a && *b) {
        if (tolower((unsigned char)*a) != tolower((unsigned char)*b)) return 0;
        a++; b++;
    }
    return *a == *b;
}

static int ci_contains(const char *text, const char *needle)
{
    size_t n = strlen(needle);
    if (n == 0) return 1;
    for (; *text; text++) {
        size_t i = 0;
        while (i < n && text[i] &&
               tolower((unsigned char)text[i]) == tolower((unsigned char)needle[i]))
            i++;
        if (i == n) return 1;
    }
    return 0;
}

/* ============================ Box drawing helpers ========================== */

static void box_top(void)    { printf("  " CYAN "┌"); repeat("─", BOX_WIDTH); printf("┐" RESET "\n"); }
static void box_middle(void) { printf("  " CYAN "├"); repeat("─", BOX_WIDTH); printf("┤" RESET "\n"); }
static void box_bottom(void) { printf("  " CYAN "└"); repeat("─", BOX_WIDTH); printf("┘" RESET "\n"); }

/* One line inside a box. `text` must be plain ASCII (no colour codes) so the
 * padding is exact; `color` colours the whole line. */
static void box_line(const char *color, const char *text)
{
    printf("  " CYAN "│" RESET "%s %-*.*s " RESET CYAN "│" RESET "\n",
           color, BOX_WIDTH - 2, BOX_WIDTH - 2, text);
}

static void banner_line(const char *color, const char *text)
{
    int pad   = BOX_WIDTH - (int)strlen(text);
    int left  = pad / 2;
    int right = pad - left;
    printf("  " CYAN "║" RESET "%s%*s%s%*s" RESET CYAN "║" RESET "\n",
           color, left, "", text, right, "");
}

static void print_banner(void)
{
    char sub[96];
    snprintf(sub, sizeof sub, "%d currencies  |  rates of %s  |  works offline",
             CURRENCY_COUNT, RATES_DATE);

    printf("\n  " CYAN "╔"); repeat("═", BOX_WIDTH); printf("╗" RESET "\n");
    banner_line("", "");
    banner_line(BOLD YELLOW, "W O R L D   C U R R E N C Y   C O N V E R T E R");
    banner_line(DIM WHITE,   sub);
    banner_line("", "");
    printf("  " CYAN "╚"); repeat("═", BOX_WIDTH); printf("╝" RESET "\n\n");
}

/* ================================ Switches ================================= */

static const char *region_name(Region r)
{
    switch (r) {
        case REG_AMERICAS: return "Americas";
        case REG_EUROPE:   return "Europe";
        case REG_ASIA:     return "Asia";
        case REG_MIDEAST:  return "Middle East";
        case REG_AFRICA:   return "Africa";
        case REG_OCEANIA:  return "Oceania";
        default:           return "Other";
    }
}

static const char *region_color(Region r)
{
    switch (r) {
        case REG_AMERICAS: return GREEN;
        case REG_EUROPE:   return BLUE;
        case REG_ASIA:     return YELLOW;
        case REG_MIDEAST:  return MAGENTA;
        case REG_AFRICA:   return RED;
        case REG_OCEANIA:  return CYAN;
        default:           return WHITE;
    }
}

/* ============================ Number formatting ============================ */

/* Writes v with `decimals` places and thousands separators.
 * Example: 1234567.5 -> "1,234,567.50" */
static void format_number(double v, int decimals, char *out, size_t size)
{
    char tmp[96];
    snprintf(tmp, sizeof tmp, "%.*f", decimals, v);

    const char *dot = strchr(tmp, '.');
    size_t int_len  = dot ? (size_t)(dot - tmp) : strlen(tmp);
    size_t start    = (tmp[0] == '-') ? 1 : 0;
    size_t o        = 0;

    if (start && o + 1 < size) out[o++] = '-';
    for (size_t i = start; i < int_len && o + 2 < size; i++) {
        out[o++] = tmp[i];
        size_t remaining = int_len - i - 1;
        if (remaining > 0 && remaining % 3 == 0) out[o++] = ',';
    }
    out[o] = '\0';
    if (dot) strncat(out, dot, size - strlen(out) - 1);
}

static void format_money(double v, char *out, size_t size)
{
    int decimals = (fabs(v) >= 1.0 || v == 0.0) ? 2 : 6;
    format_number(v, decimals, out, size);
}

static void format_rate(double v, char *out, size_t size)
{
    int decimals = (v >= 100.0) ? 2 : (v >= 1.0 ? 4 : 6);
    format_number(v, decimals, out, size);
}

/* ============================== Core logic ================================= */

/* How many units of `to` you get for 1 unit of `from`. */
static double rate_between(int from, int to)
{
    return currencies[to].per_usd / currencies[from].per_usd;
}

/* The heart of the program: convert through the USD base. */
static double convert(double amount, int from, int to)
{
    return amount / currencies[from].per_usd * currencies[to].per_usd;
}

/* Returns the table index for a 3-letter code, or -1 if not found. */
static int find_currency(const char *code)
{
    for (int i = 0; i < CURRENCY_COUNT; i++)
        if (ci_equal(currencies[i].code, code)) return i;
    return -1;
}

static void add_history(int from, int to, double amount, double result)
{
    HistoryItem *h = &history[history_next];
    snprintf(h->from, sizeof h->from, "%s", currencies[from].code);
    snprintf(h->to,   sizeof h->to,   "%s", currencies[to].code);
    h->amount = amount;
    h->result = result;
    history_next = (history_next + 1) % HISTORY_MAX;
    if (history_count < HISTORY_MAX) history_count++;
}

/* ============================== Input helpers ============================== */

/* Parses a positive amount such as "1500", "1,500.75". Returns 1 on success. */
static int parse_amount(const char *text, double *out)
{
    char clean[64];
    size_t j = 0;
    for (size_t i = 0; text[i] && j < sizeof clean - 1; i++)
        if (text[i] != ',') clean[j++] = text[i];
    clean[j] = '\0';
    if (j == 0) return 0;

    char *end = NULL;
    double v = strtod(clean, &end);
    if (*end != '\0' || !isfinite(v) || v <= 0.0 || v > MAX_AMOUNT) return 0;
    *out = v;
    return 1;
}

static double ask_amount(const char *code)
{
    char line[64], prompt[96];
    double v = 0;
    snprintf(prompt, sizeof prompt, "  " BOLD "Amount in %s" RESET " > ", code);
    for (;;) {
        read_line(prompt, line, sizeof line);
        if (parse_amount(line, &v)) return v;
        printf("  " RED "x Please enter a positive number (max 1,000,000,000,000)." RESET "\n");
    }
}

/* Asks for a region and returns it (0 = all regions, -1 = invalid). */
static int choose_region(void)
{
    char line[16];
    printf("\n  " BOLD "Choose a region" RESET "\n");
    printf("   " DIM "0" RESET "  All regions\n");
    for (int r = REG_AMERICAS; r <= REG_OCEANIA; r++)
        printf("   " DIM "%d" RESET "  %s%s" RESET "\n", r, region_color((Region)r), region_name((Region)r));
    read_line("\n  Region > ", line, sizeof line);

    switch (atoi(line)) {
        case 0: return line[0] == '0' ? 0 : -1;
        case 1: return REG_AMERICAS;
        case 2: return REG_EUROPE;
        case 3: return REG_ASIA;
        case 4: return REG_MIDEAST;
        case 5: return REG_AFRICA;
        case 6: return REG_OCEANIA;
        default: return -1;
    }
}

/* ============================== Table output =============================== */

static int pager_continue(int shown)
{
    if (shown % PAGE_SIZE != 0) return 1;
    char line[16];
    read_line(DIM "  -- Enter = next page, q = stop -- " RESET, line, sizeof line);
    return !(line[0] == 'q' || line[0] == 'Q');
}

/* Lists currencies. region == 0 means all; query == NULL/"" means no search.
 * Returns the number of currencies that matched. */
static int print_currency_table(int region, const char *query)
{
    int shown = 0, last_match = -1;
    int has_query = (query && query[0]);

    printf("\n  " BOLD CYAN "%3s  %-4s %-30s %-12s %16s" RESET "\n",
           "#", "CODE", "CURRENCY", "REGION", "1 USD =");
    printf("  " DIM); repeat("─", 70); printf(RESET "\n");

    for (int i = 0; i < CURRENCY_COUNT; i++) {
        const Currency *c = &currencies[i];
        if (region != 0 && (int)c->region != region) continue;
        if (has_query && !ci_contains(c->code, query) && !ci_contains(c->name, query)) continue;

        char rate[64];
        format_rate(c->per_usd, rate, sizeof rate);
        printf("  " DIM "%3d" RESET "  %s%-4s" RESET " %-30.30s %s%-12s" RESET " %15s%s\n",
               i + 1, region_color(c->region), c->code, c->name,
               region_color(c->region), region_name(c->region), rate,
               (c->per_usd != default_rate[i]) ? YELLOW "*" RESET : " ");
        last_match = i;
        shown++;
        if (!pager_continue(shown)) break;
    }
    if (shown == 0) printf("  " RED "No currencies found." RESET "\n");
    else printf("\n  " DIM "%d currenc%s listed.  (* = rate changed this session)" RESET "\n",
                shown, shown == 1 ? "y" : "ies");
    (void)last_match;
    return shown;
}

/* ============================ Currency selection =========================== */

static void browse_currencies(void)
{
    int region = choose_region();
    if (region < 0) {
        printf("  " RED "x Invalid choice." RESET "\n");
        return;
    }
    print_currency_table(region, NULL);
    pause_for_enter();
}

static void search_currencies(void)
{
    char q[64];
    read_line("\n  Search by code or name (e.g. 'rupee', 'dollar') > ", q, sizeof q);
    if (q[0] == '\0') return;
    print_currency_table(0, q);
    pause_for_enter();
}

/* Lets the user pick a currency by typing its code. Returns index or -1. */
static int select_currency(const char *label)
{
    char line[64];
    printf("\n  " BOLD "%s currency" RESET
           DIM "   (type a code like INR, a name like 'yen', ? to browse, 0 to cancel)" RESET "\n", label);

    for (;;) {
        read_line("  Code > ", line, sizeof line);

        if (strcmp(line, "0") == 0) return -1;
        if (strcmp(line, "?") == 0) { browse_currencies(); continue; }
        if (line[0] == '\0') continue;

        int idx = find_currency(line);
        if (idx >= 0) return idx;

        /* Not an exact code - treat the input as a search. */
        int matches = 0, only = -1;
        for (int i = 0; i < CURRENCY_COUNT; i++)
            if (ci_contains(currencies[i].code, line) || ci_contains(currencies[i].name, line)) {
                matches++; only = i;
            }

        if (matches == 1) {
            printf("  " GREEN "✓ Using %s - %s" RESET "\n", currencies[only].code, currencies[only].name);
            return only;
        }
        if (matches == 0) {
            printf("  " RED "x No currency matches '%s'. Try again." RESET "\n", line);
        } else {
            printf("  " YELLOW "%d matches - be more specific, or type the code:" RESET "\n", matches);
            print_currency_table(0, line);
        }
    }
}

/* =============================== Result cards ============================== */

static void show_result_card(int from, int to, double amount, double result)
{
    char a[64], r[64], rate[64], rev[64];
    char line[128];

    format_money(amount, a, sizeof a);
    format_money(result, r, sizeof r);
    format_rate(rate_between(from, to), rate, sizeof rate);
    format_rate(rate_between(to, from), rev,  sizeof rev);

    printf("\n");
    box_top();
    box_line(BOLD WHITE, "CONVERSION RESULT");
    box_middle();
    box_line("", "");
    snprintf(line, sizeof line, "  %s %s", a, currencies[from].code);
    box_line(WHITE, line);
    box_line(DIM, "      |");
    box_line(DIM, "      v");
    snprintf(line, sizeof line, "  %s %s", r, currencies[to].code);
    box_line(BOLD GREEN, line);
    box_line("", "");
    box_middle();
    snprintf(line, sizeof line, "Rate used : 1 %s = %s %s", currencies[from].code, rate, currencies[to].code);
    box_line(YELLOW, line);
    snprintf(line, sizeof line, "Inverse   : 1 %s = %s %s", currencies[to].code, rev, currencies[from].code);
    box_line(DIM, line);
    snprintf(line, sizeof line, "%s -> %s", currencies[from].name, currencies[to].name);
    box_line(DIM, line);
    box_bottom();
    printf("  " DIM "Rates snapshot of %s - not live market data." RESET "\n", RATES_DATE);
}

/* ================================ Features ================================= */

static void action_convert(void)
{
    clear_screen();
    print_banner();
    printf("  " BOLD MAGENTA "◆ CONVERT CURRENCY" RESET "\n");

    int from = select_currency("SOURCE");
    if (from < 0) return;
    int to = select_currency("DESTINATION");
    if (to < 0) return;

    double amount = ask_amount(currencies[from].code);

    for (;;) {
        double result = convert(amount, from, to);
        add_history(from, to, amount, result);
        show_result_card(from, to, amount, result);

        char choice[16];
        read_line("\n  [a] new amount   [s] swap currencies   [Enter] main menu > ",
                  choice, sizeof choice);
        if (choice[0] == 'a' || choice[0] == 'A') {
            amount = ask_amount(currencies[from].code);
        } else if (choice[0] == 's' || choice[0] == 'S') {
            int t = from; from = to; to = t;
            amount = ask_amount(currencies[from].code);
        } else {
            return;
        }
    }
}

static void action_multi(void)
{
    clear_screen();
    print_banner();
    printf("  " BOLD MAGENTA "◆ CONVERT ONE AMOUNT TO A WHOLE REGION" RESET "\n");

    int from = select_currency("SOURCE");
    if (from < 0) return;
    double amount = ask_amount(currencies[from].code);
    int region = choose_region();
    if (region < 0) { printf("  " RED "x Invalid choice." RESET "\n"); pause_for_enter(); return; }

    char a[64];
    format_money(amount, a, sizeof a);
    printf("\n  " BOLD "%s %s" RESET " equals:\n", a, currencies[from].code);
    printf("\n  " BOLD CYAN "%-4s %-30s %22s" RESET "\n", "CODE", "CURRENCY", "AMOUNT");
    printf("  " DIM); repeat("─", 60); printf(RESET "\n");

    int shown = 0;
    for (int i = 0; i < CURRENCY_COUNT; i++) {
        if (region != 0 && (int)currencies[i].region != region) continue;
        if (i == from) continue;
        char r[64];
        format_money(convert(amount, from, i), r, sizeof r);
        printf("  %s%-4s" RESET " %-30.30s " BOLD "%22s" RESET "\n",
               region_color(currencies[i].region), currencies[i].code, currencies[i].name, r);
        shown++;
        if (!pager_continue(shown)) break;
    }
    pause_for_enter();
}

static void action_history(void)
{
    clear_screen();
    print_banner();
    printf("  " BOLD MAGENTA "◆ RECENT CONVERSIONS" RESET "\n\n");

    if (history_count == 0) {
        printf("  " DIM "Nothing yet - make a conversion first." RESET "\n");
    } else {
        for (int k = 0; k < history_count; k++) {
            int idx = (history_next - 1 - k + HISTORY_MAX) % HISTORY_MAX;
            const HistoryItem *h = &history[idx];
            char a[64], r[64];
            format_money(h->amount, a, sizeof a);
            format_money(h->result, r, sizeof r);
            printf("  " DIM "%d." RESET "  %16s %s  " CYAN "→" RESET "  " BOLD GREEN "%16s %s" RESET "\n",
                   k + 1, a, h->from, r, h->to);
        }
    }
    pause_for_enter();
}

static void action_override_rate(void)
{
    clear_screen();
    print_banner();
    printf("  " BOLD MAGENTA "◆ CHANGE A RATE (this session only)" RESET "\n");
    printf("  " DIM "Rates are units per 1 USD. To change them permanently, edit src/rates.h." RESET "\n");

    int idx = select_currency("Which");
    if (idx < 0) return;
    if (ci_equal(currencies[idx].code, "USD")) {
        printf("  " RED "x USD is the base currency (always 1.0) and cannot be changed." RESET "\n");
        pause_for_enter();
        return;
    }

    char cur[64], line[64];
    format_rate(currencies[idx].per_usd, cur, sizeof cur);
    printf("\n  Current: 1 USD = %s %s\n", cur, currencies[idx].code);
    read_line("  New rate (units per 1 USD), or 'r' to restore default > ", line, sizeof line);

    if (line[0] == 'r' || line[0] == 'R') {
        currencies[idx].per_usd = default_rate[idx];
        printf("  " GREEN "✓ Restored default rate." RESET "\n");
    } else {
        double v;
        if (parse_amount(line, &v)) {
            currencies[idx].per_usd = v;
            format_rate(v, cur, sizeof cur);
            printf("  " GREEN "✓ Now 1 USD = %s %s" RESET "\n", cur, currencies[idx].code);
        } else {
            printf("  " RED "x Invalid rate - nothing changed." RESET "\n");
        }
    }
    pause_for_enter();
}

static void action_about(void)
{
    clear_screen();
    print_banner();
    box_top();
    box_line(BOLD WHITE, "ABOUT THIS PROGRAM");
    box_middle();
    box_line("", "");
    char when[80];
    snprintf(when, sizeof when, "(taken on %s) in src/rates.h.", RATES_DATE);
    box_line("", "This converter uses a SNAPSHOT of real exchange rates");
    box_line("", when);
    box_line("", "Rates change daily, so this is NOT live market data.");
    box_line("", "");
    box_line(YELLOW, "How a conversion works");
    box_line("", "Every rate means 'units of currency per 1 USD'.");
    box_line("", "  result = amount / rate_from * rate_to");
    box_line("", "");
    box_line(YELLOW, "How to change a rate");
    box_line("", "Open src/rates.h, edit the number on the currency's");
    box_line("", "line, then run 'make' again. Use menu option 6 for a");
    box_line("", "temporary change while the program is running.");
    box_line("", "");
    box_bottom();
    pause_for_enter();
}

/* ================================ Main menu ================================ */

static void print_menu(void)
{
    box_top();
    box_line(BOLD WHITE, "MAIN MENU");
    box_middle();
    box_line(WHITE, "[1]  Convert currency");
    box_line(WHITE, "[2]  Convert one amount to a whole region");
    box_line(WHITE, "[3]  Browse all currencies & rates");
    box_line(WHITE, "[4]  Search currencies by code or name");
    box_line(WHITE, "[5]  Recent conversions");
    box_line(WHITE, "[6]  Change a rate (this session)");
    box_line(WHITE, "[7]  About & how rates work");
    box_line(RED,   "[0]  Exit");
    box_bottom();
}

int main(void)
{
    setup_terminal();

    for (int i = 0; i < CURRENCY_COUNT; i++)      /* remember original rates */
        default_rate[i] = currencies[i].per_usd;

    char choice[16];
    for (;;) {
        clear_screen();
        print_banner();
        print_menu();
        read_line("\n  Select an option > ", choice, sizeof choice);

        switch (choice[0]) {
            case '1': action_convert();        break;
            case '2': action_multi();          break;
            case '3': browse_currencies();     break;
            case '4': search_currencies();     break;
            case '5': action_history();        break;
            case '6': action_override_rate();  break;
            case '7': action_about();          break;
            case '0':
            case 'q':
            case 'Q':
                printf("\n  " CYAN "Thank you for using World Currency Converter. Goodbye!" RESET "\n\n");
                return 0;
            default:
                printf("  " RED "x Invalid option - please choose 0-7." RESET "\n");
                pause_for_enter();
        }
    }
}
