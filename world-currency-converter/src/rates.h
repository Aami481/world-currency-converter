/* ============================================================================
 *  rates.h  -  EXCHANGE RATE TABLE (SNAPSHOT)
 * ============================================================================
 *  !!  SNAPSHOT OF REAL RATES DATED 2026-11-01 - NOT LIVE DATA  !!
 *  Source: open currency-api data (mid-market rates). Rates change daily,
 *  so edit the numbers below whenever you want fresher values.
 *
 *  Every rate is expressed as:   units of currency  per  1 US Dollar (USD)
 *
 *      Example: {"INR", "Indian Rupee", REG_ASIA, 95.01}
 *               means  1 USD = 95.01 INR
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
#define RATES_DATE "2026-11-01"

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
    {"CAD", "Canadian Dollar",            REG_AMERICAS,      1.3969},
    {"MXN", "Mexican Peso",               REG_AMERICAS,     18.7730},
    {"BRL", "Brazilian Real",             REG_AMERICAS,      5.4063},
    {"ARS", "Argentine Peso",             REG_AMERICAS,     1535.35},
    {"CLP", "Chilean Peso",               REG_AMERICAS,    993.6825},
    {"COP", "Colombian Peso",             REG_AMERICAS,     3201.17},
    {"PEN", "Peruvian Sol",               REG_AMERICAS,      3.4655},
    {"UYU", "Uruguayan Peso",             REG_AMERICAS,     40.1689},
    {"PYG", "Paraguayan Guarani",         REG_AMERICAS,     5941.74},
    {"BOB", "Bolivian Boliviano",         REG_AMERICAS,     12.1196},
    {"VES", "Venezuelan Bolivar",         REG_AMERICAS,    887.7868},
    {"GYD", "Guyanese Dollar",            REG_AMERICAS,    209.4275},
    {"SRD", "Surinamese Dollar",          REG_AMERICAS,     37.6640},
    {"CRC", "Costa Rican Colon",          REG_AMERICAS,    452.9334},
    {"GTQ", "Guatemalan Quetzal",         REG_AMERICAS,      7.6420},
    {"HNL", "Honduran Lempira",           REG_AMERICAS,     26.9531},
    {"NIO", "Nicaraguan Cordoba",         REG_AMERICAS,     36.7202},
    {"PAB", "Panamanian Balboa",          REG_AMERICAS,      1.0000},
    {"BZD", "Belize Dollar",              REG_AMERICAS,      2.0118},
    {"DOP", "Dominican Peso",             REG_AMERICAS,     60.3932},
    {"HTG", "Haitian Gourde",             REG_AMERICAS,    131.3835},
    {"JMD", "Jamaican Dollar",            REG_AMERICAS,    158.7474},
    {"CUP", "Cuban Peso",                 REG_AMERICAS,     23.9733},
    {"TTD", "Trinidad & Tobago Dollar",   REG_AMERICAS,      6.7577},
    {"BSD", "Bahamian Dollar",            REG_AMERICAS,      1.0000},
    {"BBD", "Barbadian Dollar",           REG_AMERICAS,      2.0000},
    {"XCD", "East Caribbean Dollar",      REG_AMERICAS,      2.7000},
    {"AWG", "Aruban Florin",              REG_AMERICAS,      1.7900},
    {"ANG", "Netherlands Antillean Guilder", REG_AMERICAS,      1.7930},
    {"KYD", "Cayman Islands Dollar",      REG_AMERICAS,    0.823683},
    {"BMD", "Bermudian Dollar",           REG_AMERICAS,      1.0000},

    /* ------------------------------- EUROPE ------------------------------- */
    {"EUR", "Euro",                       REG_EUROPE,    0.892533},
    {"GBP", "British Pound",              REG_EUROPE,    0.746493},
    {"CHF", "Swiss Franc",                REG_EUROPE,    0.824181},
    {"SEK", "Swedish Krona",              REG_EUROPE,      9.8253},
    {"NOK", "Norwegian Krone",            REG_EUROPE,      9.2038},
    {"DKK", "Danish Krone",               REG_EUROPE,      6.6949},
    {"ISK", "Icelandic Krona",            REG_EUROPE,    121.7252},
    {"PLN", "Polish Zloty",               REG_EUROPE,      3.9467},
    {"CZK", "Czech Koruna",               REG_EUROPE,     21.8131},
    {"HUF", "Hungarian Forint",           REG_EUROPE,    327.9329},
    {"RON", "Romanian Leu",               REG_EUROPE,      4.7641},
    {"BGN", "Bulgarian Lev",              REG_EUROPE,      1.7456},
    {"RSD", "Serbian Dinar",              REG_EUROPE,    105.3348},
    {"BAM", "Bosnia-Herzegovina Mark",    REG_EUROPE,      1.7456},
    {"MKD", "Macedonian Denar",           REG_EUROPE,     54.9834},
    {"ALL", "Albanian Lek",               REG_EUROPE,     81.5130},
    {"MDL", "Moldovan Leu",               REG_EUROPE,     18.0221},
    {"UAH", "Ukrainian Hryvnia",          REG_EUROPE,     45.4641},
    {"BYN", "Belarusian Ruble",           REG_EUROPE,      2.9425},
    {"RUB", "Russian Ruble",              REG_EUROPE,     80.3126},
    {"GEL", "Georgian Lari",              REG_EUROPE,      2.5950},
    {"AMD", "Armenian Dram",              REG_EUROPE,    360.6252},
    {"AZN", "Azerbaijani Manat",          REG_EUROPE,      1.7009},
    {"GIP", "Gibraltar Pound",            REG_EUROPE,    0.746493},
    {"JEP", "Jersey Pound",               REG_EUROPE,    0.746493},
    {"IMP", "Manx Pound",                 REG_EUROPE,    0.746493},

    /* -------------------------------- ASIA -------------------------------- */
    {"INR", "Indian Rupee",               REG_ASIA,     95.0069},
    {"PKR", "Pakistani Rupee",            REG_ASIA,    276.8170},
    {"BDT", "Bangladeshi Taka",           REG_ASIA,    124.3083},
    {"LKR", "Sri Lankan Rupee",           REG_ASIA,    332.5572},
    {"NPR", "Nepalese Rupee",             REG_ASIA,    152.0823},
    {"BTN", "Bhutanese Ngultrum",         REG_ASIA,     95.0069},
    {"MVR", "Maldivian Rufiyaa",          REG_ASIA,     15.4750},
    {"AFN", "Afghan Afghani",             REG_ASIA,     65.0105},
    {"CNY", "Chinese Yuan",               REG_ASIA,      6.6564},
    {"JPY", "Japanese Yen",               REG_ASIA,    157.5730},
    {"KRW", "South Korean Won",           REG_ASIA,     1336.00},
    {"KPW", "North Korean Won",           REG_ASIA,    900.1298},
    {"HKD", "Hong Kong Dollar",           REG_ASIA,      7.8452},
    {"TWD", "New Taiwan Dollar",          REG_ASIA,     32.6372},
    {"MOP", "Macanese Pataca",            REG_ASIA,      8.0806},
    {"MNT", "Mongolian Tugrik",           REG_ASIA,     3599.32},
    {"SGD", "Singapore Dollar",           REG_ASIA,      1.2782},
    {"MYR", "Malaysian Ringgit",          REG_ASIA,      4.0601},
    {"THB", "Thai Baht",                  REG_ASIA,     33.7313},
    {"IDR", "Indonesian Rupiah",          REG_ASIA,    18105.52},
    {"PHP", "Philippine Peso",            REG_ASIA,     63.6571},
    {"VND", "Vietnamese Dong",            REG_ASIA,    25798.97},
    {"KHR", "Cambodian Riel",             REG_ASIA,     4080.99},
    {"LAK", "Lao Kip",                    REG_ASIA,    22463.78},
    {"MMK", "Myanmar Kyat",               REG_ASIA,     2099.33},
    {"BND", "Brunei Dollar",              REG_ASIA,      1.2782},
    {"KZT", "Kazakhstani Tenge",          REG_ASIA,    453.6737},
    {"UZS", "Uzbekistani Som",            REG_ASIA,    12007.64},
    {"KGS", "Kyrgyzstani Som",            REG_ASIA,     87.4552},
    {"TJS", "Tajikistani Somoni",         REG_ASIA,      9.2088},
    {"TMT", "Turkmenistani Manat",        REG_ASIA,      3.5168},

    /* ---------------------------- MIDDLE EAST ----------------------------- */
    {"AED", "UAE Dirham",                 REG_MIDEAST,      3.6725},
    {"SAR", "Saudi Riyal",                REG_MIDEAST,      3.7500},
    {"QAR", "Qatari Riyal",               REG_MIDEAST,      3.6400},
    {"KWD", "Kuwaiti Dinar",              REG_MIDEAST,    0.310509},
    {"BHD", "Bahraini Dinar",             REG_MIDEAST,    0.376000},
    {"OMR", "Omani Rial",                 REG_MIDEAST,    0.385012},
    {"JOD", "Jordanian Dinar",            REG_MIDEAST,    0.709000},
    {"ILS", "Israeli New Shekel",         REG_MIDEAST,      3.1133},
    {"TRY", "Turkish Lira",               REG_MIDEAST,     49.9531},
    {"IQD", "Iraqi Dinar",                REG_MIDEAST,     1514.18},
    {"IRR", "Iranian Rial",               REG_MIDEAST,  1868684.48},
    {"LBP", "Lebanese Pound",             REG_MIDEAST,    89882.90},
    {"SYP", "Syrian Pound",               REG_MIDEAST,    13003.87},
    {"YER", "Yemeni Rial",                REG_MIDEAST,    236.1818},

    /* ------------------------------- AFRICA ------------------------------- */
    {"ZAR", "South African Rand",         REG_AFRICA,     16.6842},
    {"NGN", "Nigerian Naira",             REG_AFRICA,     1347.76},
    {"EGP", "Egyptian Pound",             REG_AFRICA,     55.9968},
    {"KES", "Kenyan Shilling",            REG_AFRICA,    129.9320},
    {"GHS", "Ghanaian Cedi",              REG_AFRICA,     11.6427},
    {"TZS", "Tanzanian Shilling",         REG_AFRICA,     2642.18},
    {"UGX", "Ugandan Shilling",           REG_AFRICA,     4256.00},
    {"ETB", "Ethiopian Birr",             REG_AFRICA,    161.3284},
    {"MAD", "Moroccan Dirham",            REG_AFRICA,      9.8439},
    {"DZD", "Algerian Dinar",             REG_AFRICA,    135.8290},
    {"TND", "Tunisian Dinar",             REG_AFRICA,      2.9923},
    {"LYD", "Libyan Dinar",               REG_AFRICA,      6.4272},
    {"SDG", "Sudanese Pound",             REG_AFRICA,    600.2243},
    {"SSP", "South Sudanese Pound",       REG_AFRICA,     5745.22},
    {"ZMW", "Zambian Kwacha",             REG_AFRICA,     20.2367},
    {"ZWG", "Zimbabwe Gold",              REG_AFRICA,     26.7882},
    {"BWP", "Botswana Pula",              REG_AFRICA,     13.9262},
    {"NAD", "Namibian Dollar",            REG_AFRICA,     16.6842},
    {"SZL", "Eswatini Lilangeni",         REG_AFRICA,     16.6842},
    {"LSL", "Lesotho Loti",               REG_AFRICA,     16.6842},
    {"MZN", "Mozambican Metical",         REG_AFRICA,     63.8963},
    {"AOA", "Angolan Kwanza",             REG_AFRICA,    924.5028},
    {"MWK", "Malawian Kwacha",            REG_AFRICA,     1738.13},
    {"MGA", "Malagasy Ariary",            REG_AFRICA,     4591.04},
    {"MUR", "Mauritian Rupee",            REG_AFRICA,     47.2952},
    {"SCR", "Seychellois Rupee",          REG_AFRICA,     14.3717},
    {"XOF", "West African CFA Franc",     REG_AFRICA,    585.4631},
    {"XAF", "Central African CFA Franc",  REG_AFRICA,    585.4631},
    {"CDF", "Congolese Franc",            REG_AFRICA,     2272.99},
    {"RWF", "Rwandan Franc",              REG_AFRICA,     1475.93},
    {"BIF", "Burundian Franc",            REG_AFRICA,     2996.72},
    {"DJF", "Djiboutian Franc",           REG_AFRICA,    178.3213},
    {"KMF", "Comorian Franc",             REG_AFRICA,    439.0974},
    {"ERN", "Eritrean Nakfa",             REG_AFRICA,     15.0000},
    {"SOS", "Somali Shilling",            REG_AFRICA,    571.4923},
    {"GMD", "Gambian Dalasi",             REG_AFRICA,     74.0563},
    {"GNF", "Guinean Franc",              REG_AFRICA,     8848.18},
    {"SLE", "Sierra Leonean Leone",       REG_AFRICA,     22.9451},
    {"LRD", "Liberian Dollar",            REG_AFRICA,    170.2220},
    {"CVE", "Cape Verdean Escudo",        REG_AFRICA,     98.4196},
    {"STN", "Sao Tome & Principe Dobra",  REG_AFRICA,     22.0801},
    {"MRU", "Mauritanian Ouguiya",        REG_AFRICA,     40.4301},

    /* ------------------------------- OCEANIA ------------------------------ */
    {"AUD", "Australian Dollar",          REG_OCEANIA,      1.4226},
    {"NZD", "New Zealand Dollar",         REG_OCEANIA,      1.7758},
    {"FJD", "Fijian Dollar",              REG_OCEANIA,      2.2477},
    {"PGK", "Papua New Guinean Kina",     REG_OCEANIA,      4.5546},
    {"WST", "Samoan Tala",                REG_OCEANIA,      2.7762},
    {"TOP", "Tongan Pa'anga",             REG_OCEANIA,      2.3897},
    {"VUV", "Vanuatu Vatu",               REG_OCEANIA,    118.9626},
    {"SBD", "Solomon Islands Dollar",     REG_OCEANIA,      8.0497},
    {"XPF", "CFP Franc",                  REG_OCEANIA,    106.5075}
};

/* Number of currencies - calculated automatically, never edit by hand. */
#define CURRENCY_COUNT ((int)(sizeof(currencies) / sizeof(currencies[0])))

#endif /* RATES_H */
