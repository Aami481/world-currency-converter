/* ============================================================================
 *  rates.h  -  EXCHANGE RATE TABLE (SNAPSHOT)
 * ============================================================================
 *  !!  SNAPSHOT OF REAL RATES DATED 2026-10-29 - NOT LIVE DATA  !!
 *  Source: open currency-api data (mid-market rates). Rates change daily,
 *  so edit the numbers below whenever you want fresher values.
 *
 *  Every rate is expressed as:   units of currency  per  1 US Dollar (USD)
 *
 *      Example: {"INR", "Indian Rupee", REG_ASIA, 95.26}
 *               means  1 USD = 95.26 INR
 *
 *  HOW TO CHANGE A RATE
 *      1. Find the currency line below (they are grouped by region).
 *      2. Edit the last number on that line.
 *      3. Re-compile:  make
 *
 *  HOW TO ADD A CURRENCY
 *      Add one new line inside the array. The program counts the entries
 *      automatically (CURRENCY_COUNT) - nothing else needs to change.
 * ========================================================================== */
#ifndef RATES_H
#define RATES_H

/* Date the rate table below was taken (shown in the program). */
#define RATES_DATE "2026-10-29"

typedef enum {
    REG_AMERICAS = 1,
    REG_EUROPE,
    REG_ASIA,
    REG_MIDEAST,
    REG_AFRICA,
    REG_OCEANIA
} Region;

typedef struct {
    const char *code;    /* ISO 4217 style 3-letter code            */
    const char *name;    /* Currency name                           */
    Region      region;  /* Used for filtering / colouring          */
    double      per_usd; /* SAMPLE rate: units of this currency per 1 USD */
} Currency;

static Currency currencies[] = {
    /* ------------------------------ AMERICAS ------------------------------ */
    {"USD", "US Dollar",                  REG_AMERICAS,      1.0000},
    {"CAD", "Canadian Dollar",            REG_AMERICAS,      1.3986},
    {"MXN", "Mexican Peso",               REG_AMERICAS,     18.6704},
    {"BRL", "Brazilian Real",             REG_AMERICAS,      5.3466},
    {"ARS", "Argentine Peso",             REG_AMERICAS,     1541.64},
    {"CLP", "Chilean Peso",               REG_AMERICAS,    987.5754},
    {"COP", "Colombian Peso",             REG_AMERICAS,     3167.60},
    {"PEN", "Peruvian Sol",               REG_AMERICAS,      3.4492},
    {"UYU", "Uruguayan Peso",             REG_AMERICAS,     40.1620},
    {"PYG", "Paraguayan Guarani",         REG_AMERICAS,     5773.93},
    {"BOB", "Bolivian Boliviano",         REG_AMERICAS,     12.0113},
    {"VES", "Venezuelan Bolivar",         REG_AMERICAS,    887.2864},
    {"GYD", "Guyanese Dollar",            REG_AMERICAS,    209.2673},
    {"SRD", "Surinamese Dollar",          REG_AMERICAS,     37.6552},
    {"CRC", "Costa Rican Colon",          REG_AMERICAS,    454.6170},
    {"GTQ", "Guatemalan Quetzal",         REG_AMERICAS,      7.6401},
    {"HNL", "Honduran Lempira",           REG_AMERICAS,     26.8571},
    {"NIO", "Nicaraguan Cordoba",         REG_AMERICAS,     36.7767},
    {"PAB", "Panamanian Balboa",          REG_AMERICAS,      1.0000},
    {"BZD", "Belize Dollar",              REG_AMERICAS,      2.0117},
    {"DOP", "Dominican Peso",             REG_AMERICAS,     60.8645},
    {"HTG", "Haitian Gourde",             REG_AMERICAS,    130.8950},
    {"JMD", "Jamaican Dollar",            REG_AMERICAS,    158.4941},
    {"CUP", "Cuban Peso",                 REG_AMERICAS,     23.9588},
    {"TTD", "Trinidad & Tobago Dollar",   REG_AMERICAS,      6.7854},
    {"BSD", "Bahamian Dollar",            REG_AMERICAS,      1.0000},
    {"BBD", "Barbadian Dollar",           REG_AMERICAS,      2.0000},
    {"XCD", "East Caribbean Dollar",      REG_AMERICAS,      2.7072},
    {"AWG", "Aruban Florin",              REG_AMERICAS,      1.7900},
    {"ANG", "Netherlands Antillean Guilder", REG_AMERICAS,      1.7999},
    {"KYD", "Cayman Islands Dollar",      REG_AMERICAS,    0.831018},
    {"BMD", "Bermudian Dollar",           REG_AMERICAS,      1.0000},

    /* ------------------------------- EUROPE ------------------------------- */
    {"EUR", "Euro",                       REG_EUROPE,    0.897394},
    {"GBP", "British Pound",              REG_EUROPE,    0.750769},
    {"CHF", "Swiss Franc",                REG_EUROPE,    0.828867},
    {"SEK", "Swedish Krona",              REG_EUROPE,      9.9117},
    {"NOK", "Norwegian Krone",            REG_EUROPE,      9.2573},
    {"DKK", "Danish Krone",               REG_EUROPE,      6.7070},
    {"ISK", "Icelandic Krona",            REG_EUROPE,    121.8623},
    {"PLN", "Polish Zloty",               REG_EUROPE,      3.9494},
    {"CZK", "Czech Koruna",               REG_EUROPE,     21.8656},
    {"HUF", "Hungarian Forint",           REG_EUROPE,    329.2521},
    {"RON", "Romanian Leu",               REG_EUROPE,      4.8015},
    {"BGN", "Bulgarian Lev",              REG_EUROPE,      1.7551},
    {"RSD", "Serbian Dinar",              REG_EUROPE,    105.4940},
    {"BAM", "Bosnia-Herzegovina Mark",    REG_EUROPE,      1.7551},
    {"MKD", "Macedonian Denar",           REG_EUROPE,     55.2262},
    {"ALL", "Albanian Lek",               REG_EUROPE,     81.5298},
    {"MDL", "Moldovan Leu",               REG_EUROPE,     17.9883},
    {"UAH", "Ukrainian Hryvnia",          REG_EUROPE,     45.5360},
    {"BYN", "Belarusian Ruble",           REG_EUROPE,      2.9424},
    {"RUB", "Russian Ruble",              REG_EUROPE,     80.4945},
    {"GEL", "Georgian Lari",              REG_EUROPE,      2.5932},
    {"AMD", "Armenian Dram",              REG_EUROPE,    358.7526},
    {"AZN", "Azerbaijani Manat",          REG_EUROPE,      1.7000},
    {"GIP", "Gibraltar Pound",            REG_EUROPE,    0.750769},
    {"JEP", "Jersey Pound",               REG_EUROPE,    0.750769},
    {"IMP", "Manx Pound",                 REG_EUROPE,    0.750769},

    /* -------------------------------- ASIA -------------------------------- */
    {"INR", "Indian Rupee",               REG_ASIA,     95.2592},
    {"PKR", "Pakistani Rupee",            REG_ASIA,    276.3353},
    {"BDT", "Bangladeshi Taka",           REG_ASIA,    124.0367},
    {"LKR", "Sri Lankan Rupee",           REG_ASIA,    332.1994},
    {"NPR", "Nepalese Rupee",             REG_ASIA,    152.4862},
    {"BTN", "Bhutanese Ngultrum",         REG_ASIA,     95.2592},
    {"MVR", "Maldivian Rufiyaa",          REG_ASIA,     15.4591},
    {"AFN", "Afghan Afghani",             REG_ASIA,     64.7232},
    {"CNY", "Chinese Yuan",               REG_ASIA,      6.6623},
    {"JPY", "Japanese Yen",               REG_ASIA,    157.8581},
    {"KRW", "South Korean Won",           REG_ASIA,     1336.07},
    {"KPW", "North Korean Won",           REG_ASIA,    899.9431},
    {"HKD", "Hong Kong Dollar",           REG_ASIA,      7.8454},
    {"TWD", "New Taiwan Dollar",          REG_ASIA,     32.5611},
    {"MOP", "Macanese Pataca",            REG_ASIA,      8.0808},
    {"MNT", "Mongolian Tugrik",           REG_ASIA,     3601.49},
    {"SGD", "Singapore Dollar",           REG_ASIA,      1.2805},
    {"MYR", "Malaysian Ringgit",          REG_ASIA,      4.0641},
    {"THB", "Thai Baht",                  REG_ASIA,     33.7425},
    {"IDR", "Indonesian Rupiah",          REG_ASIA,    18116.73},
    {"PHP", "Philippine Peso",            REG_ASIA,     63.8550},
    {"VND", "Vietnamese Dong",            REG_ASIA,    25836.19},
    {"KHR", "Cambodian Riel",             REG_ASIA,     4077.61},
    {"LAK", "Lao Kip",                    REG_ASIA,    22510.75},
    {"MMK", "Myanmar Kyat",               REG_ASIA,     2099.85},
    {"BND", "Brunei Dollar",              REG_ASIA,      1.2805},
    {"KZT", "Kazakhstani Tenge",          REG_ASIA,    455.2715},
    {"UZS", "Uzbekistani Som",            REG_ASIA,    12003.24},
    {"KGS", "Kyrgyzstani Som",            REG_ASIA,     87.4602},
    {"TJS", "Tajikistani Somoni",         REG_ASIA,      9.2004},
    {"TMT", "Turkmenistani Manat",        REG_ASIA,      3.5095},

    /* ---------------------------- MIDDLE EAST ----------------------------- */
    {"AED", "UAE Dirham",                 REG_MIDEAST,      3.6725},
    {"SAR", "Saudi Riyal",                REG_MIDEAST,      3.7500},
    {"QAR", "Qatari Riyal",               REG_MIDEAST,      3.6400},
    {"KWD", "Kuwaiti Dinar",              REG_MIDEAST,    0.311044},
    {"BHD", "Bahraini Dinar",             REG_MIDEAST,    0.376000},
    {"OMR", "Omani Rial",                 REG_MIDEAST,    0.384903},
    {"JOD", "Jordanian Dinar",            REG_MIDEAST,    0.709000},
    {"ILS", "Israeli New Shekel",         REG_MIDEAST,      3.1195},
    {"TRY", "Turkish Lira",               REG_MIDEAST,     49.8381},
    {"IQD", "Iraqi Dinar",                REG_MIDEAST,     1514.93},
    {"IRR", "Iranian Rial",               REG_MIDEAST,  1864532.10},
    {"LBP", "Lebanese Pound",             REG_MIDEAST,    90239.18},
    {"SYP", "Syrian Pound",               REG_MIDEAST,    13001.18},
    {"YER", "Yemeni Rial",                REG_MIDEAST,    236.1364},

    /* ------------------------------- AFRICA ------------------------------- */
    {"ZAR", "South African Rand",         REG_AFRICA,     16.6117},
    {"NGN", "Nigerian Naira",             REG_AFRICA,     1345.46},
    {"EGP", "Egyptian Pound",             REG_AFRICA,     56.1150},
    {"KES", "Kenyan Shilling",            REG_AFRICA,    129.9431},
    {"GHS", "Ghanaian Cedi",              REG_AFRICA,     11.6350},
    {"TZS", "Tanzanian Shilling",         REG_AFRICA,     2645.62},
    {"UGX", "Ugandan Shilling",           REG_AFRICA,     4354.12},
    {"ETB", "Ethiopian Birr",             REG_AFRICA,    163.0387},
    {"MAD", "Moroccan Dirham",            REG_AFRICA,      9.8510},
    {"DZD", "Algerian Dinar",             REG_AFRICA,    135.2537},
    {"TND", "Tunisian Dinar",             REG_AFRICA,      2.9944},
    {"LYD", "Libyan Dinar",               REG_AFRICA,      6.4238},
    {"SDG", "Sudanese Pound",             REG_AFRICA,    600.1755},
    {"SSP", "South Sudanese Pound",       REG_AFRICA,     5745.20},
    {"ZMW", "Zambian Kwacha",             REG_AFRICA,     20.1695},
    {"ZWG", "Zimbabwe Gold",              REG_AFRICA,     26.8354},
    {"BWP", "Botswana Pula",              REG_AFRICA,     13.8043},
    {"NAD", "Namibian Dollar",            REG_AFRICA,     16.6117},
    {"SZL", "Eswatini Lilangeni",         REG_AFRICA,     16.6117},
    {"LSL", "Lesotho Loti",               REG_AFRICA,     16.6117},
    {"MZN", "Mozambican Metical",         REG_AFRICA,     63.8635},
    {"AOA", "Angolan Kwanza",             REG_AFRICA,    918.0861},
    {"MWK", "Malawian Kwacha",            REG_AFRICA,     1731.56},
    {"MGA", "Malagasy Ariary",            REG_AFRICA,     4569.35},
    {"MUR", "Mauritian Rupee",            REG_AFRICA,     47.4661},
    {"SCR", "Seychellois Rupee",          REG_AFRICA,     14.7302},
    {"XOF", "West African CFA Franc",     REG_AFRICA,    588.6516},
    {"XAF", "Central African CFA Franc",  REG_AFRICA,    588.6516},
    {"CDF", "Congolese Franc",            REG_AFRICA,     2314.49},
    {"RWF", "Rwandan Franc",              REG_AFRICA,     1477.20},
    {"BIF", "Burundian Franc",            REG_AFRICA,     2998.74},
    {"DJF", "Djiboutian Franc",           REG_AFRICA,    178.3061},
    {"KMF", "Comorian Franc",             REG_AFRICA,    441.4887},
    {"ERN", "Eritrean Nakfa",             REG_AFRICA,     15.0000},
    {"SOS", "Somali Shilling",            REG_AFRICA,    571.4439},
    {"GMD", "Gambian Dalasi",             REG_AFRICA,     74.1362},
    {"GNF", "Guinean Franc",              REG_AFRICA,     8840.74},
    {"SLE", "Sierra Leonean Leone",       REG_AFRICA,     22.9200},
    {"LRD", "Liberian Dollar",            REG_AFRICA,    170.5928},
    {"CVE", "Cape Verdean Escudo",        REG_AFRICA,     98.9556},
    {"STN", "Sao Tome & Principe Dobra",  REG_AFRICA,     22.1537},
    {"MRU", "Mauritanian Ouguiya",        REG_AFRICA,     40.4245},

    /* ------------------------------- OCEANIA ------------------------------ */
    {"AUD", "Australian Dollar",          REG_OCEANIA,      1.4175},
    {"NZD", "New Zealand Dollar",         REG_OCEANIA,      1.7789},
    {"FJD", "Fijian Dollar",              REG_OCEANIA,      2.2420},
    {"PGK", "Papua New Guinean Kina",     REG_OCEANIA,      4.4608},
    {"WST", "Samoan Tala",                REG_OCEANIA,      2.7599},
    {"TOP", "Tongan Pa'anga",             REG_OCEANIA,      2.4080},
    {"VUV", "Vanuatu Vatu",               REG_OCEANIA,    119.6585},
    {"SBD", "Solomon Islands Dollar",     REG_OCEANIA,      8.0504},
    {"XPF", "CFP Franc",                  REG_OCEANIA,    107.0875}
};

/* Number of currencies - calculated automatically, never edit by hand. */
#define CURRENCY_COUNT ((int)(sizeof(currencies) / sizeof(currencies[0])))

#endif /* RATES_H */
