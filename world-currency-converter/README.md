<div align="center">

# 💱 World Currency Converter

**A beautiful, colourful terminal currency converter written in pure C.**
154 currencies · real rates snapshot (2026-10-29) · works 100% offline

![Language](https://img.shields.io/badge/language-C99-00599C?logo=c&logoColor=white)
![Currencies](https://img.shields.io/badge/currencies-154-brightgreen)
![Platform](https://img.shields.io/badge/platform-Windows%20%7C%20Linux%20%7C%20macOS-blue)
![License](https://img.shields.io/badge/license-MIT-yellow)

</div>

---

> ℹ️ **About the rates** — the C program uses a **snapshot of real exchange rates taken on 2026-10-29**
> (open currency-api data), stored in [`src/rates.h`](src/rates.h). Rates change every day, so this is
> **not live data** and must not be used for real financial decisions. The web version fetches live rates when online.

## ✨ Features

| Feature | Description |
|---|---|
| 🌍 **154 currencies** | Americas, Europe, Asia, Middle East, Africa and Oceania |
| 🔄 **Convert any pair** | Pick a source and destination, enter an amount, get the result instantly |
| 📊 **Rate displayed** | Every result shows the rate used *and* the inverse rate |
| 🗺️ **Region conversion** | Convert one amount into every currency of a region at once |
| 🔎 **Smart search** | Type a code (`INR`) or a name (`yen`, `rupee`, `dollar`) |
| 🕘 **History** | Remembers your last 8 conversions |
| ✏️ **Editable rates** | Change rates in the code (permanent) or while running (session) |
| 🎨 **Beautiful UI** | Coloured, box-drawn terminal interface with regional colour coding |
| 🛡️ **Robust input** | Validates every input; accepts `1,500.75`; handles Ctrl+D / Ctrl+Z |

## 🖥️ Preview

```text
  ╔══════════════════════════════════════════════════════════════╗
  ║                                                              ║
  ║       W O R L D   C U R R E N C Y   C O N V E R T E R        ║
  ║      154 currencies  |  rates of 2026-10-29  |  works offline   ║
  ║                                                              ║
  ╚══════════════════════════════════════════════════════════════╝

  ┌──────────────────────────────────────────────────────────────┐
  │ CONVERSION RESULT                                            │
  ├──────────────────────────────────────────────────────────────┤
  │                                                              │
  │   1,000.00 USD                                               │
  │       |                                                      │
  │       v                                                      │
  │   95,259.21 INR                                              │
  │                                                              │
  ├──────────────────────────────────────────────────────────────┤
  │ Rate used : 1 USD = 95.2592 INR                              │
  │ Inverse   : 1 INR = 0.010498 USD                             │
  │ US Dollar -> Indian Rupee                                    │
  └──────────────────────────────────────────────────────────────┘
```

> 📸 *Tip: replace the block above with a real screenshot — save it as `docs/screenshot.png`
> and use `![Screenshot](docs/screenshot.png)`.*

## 🚀 Getting Started

### Requirements
- A C compiler (GCC, Clang, or MinGW on Windows)
- `make` *(optional — you can compile with one command)*

### Build & run

**Linux / macOS**
```bash
git clone https://github.com/<your-username>/world-currency-converter.git
cd world-currency-converter
make run
```

**Windows (MinGW / MSYS2)**
```bash
gcc -std=c99 -O2 -o currency_converter.exe src/main.c -lm
currency_converter.exe
```

**Without make (any OS)**
```bash
gcc -std=c99 -O2 -o currency_converter src/main.c -lm
./currency_converter
```

> 💡 On Windows use **Windows Terminal** or PowerShell for the best colours and box-drawing
> characters. The program enables UTF-8 and ANSI colours automatically.

## 🧮 How the conversion works

Every rate in `rates.h` is stored as **units of that currency per 1 US Dollar**.
To convert between *any* two currencies the program goes through USD:

```text
result = amount ÷ rate_from × rate_to
```

Example: 50 EUR → INR with `EUR = 0.8974` and `INR = 95.2592`

```text
50 ÷ 0.8974 × 95.2592 ≈ 5,307.55 INR
```

One table of 154 numbers therefore supports **23,562 currency pairs**.

## ✏️ Updating or changing the rates

**Refreshing / editing (in code)** — open [`src/rates.h`](src/rates.h), find the currency and edit the
last number, then rebuild:

```c
{"INR", "Indian Rupee", REG_ASIA, 95.2592},   /* 1 USD = 95.26 INR */
```

**Temporarily (while running)** — choose **`[6] Change a rate`** from the menu. Changed
rates are marked with a yellow `*` in the tables, and can be restored by typing `r`.

**Adding a currency** — add one new line to the array in `rates.h`. The program counts the
entries automatically, so nothing else needs changing.

## 📚 C concepts demonstrated

| Concept | Where it is used |
|---|---|
| **`switch`** | Main menu dispatch, `region_name()`, `region_color()`, region selection |
| **Functions** | ~35 small single-purpose functions (`convert()`, `format_money()`, `select_currency()` …) |
| **Arrays** | `currencies[]` rate table, `history[]` ring buffer, `default_rate[]`, text buffers |
| **Arithmetic** | Cross-rate formula, thousands-separator formatting, ring-buffer index maths |
| **Structs & enums** | `Currency`, `HistoryItem`, `Region` |
| **Input validation** | `strtod()` parsing, bounds checks, `isfinite()` |

## 📁 Project structure

```text
world-currency-converter/
├── src/
│   ├── main.c        # program logic and terminal UI
│   └── rates.h       # ★ the exchange-rate table (edit rates here)
├── Makefile          # make / make run / make clean
├── README.md
├── LICENSE
└── .gitignore
```

## 🌐 Publishing to GitHub

```bash
git init
git add .
git commit -m "Initial commit: World Currency Converter"
git branch -M main
git remote add origin https://github.com/<your-username>/world-currency-converter.git
git push -u origin main
```

## 🔮 Ideas for the future

- Load rates from a CSV file instead of a header
- Save conversion history to disk
- Optional live-rate mode using libcurl and a public exchange-rate API

## 📄 License

Released under the [MIT License](LICENSE).

## 🌐 Bonus: Web version

A browser version with the same 154 currencies, which loads **live rates** when online (and falls back to the snapshot offline), lives in [`web/index.html`](web/index.html).
Just double-click the file to open it, no installation needed (live rates need internet). It features searchable currency
pickers, a swap button, live results, quick-amount chips, and automatic dark mode.

To host it free on **GitHub Pages**: *Settings → Pages → Deploy from a branch → `main` → `/ (root)`*,
then open `https://<your-username>.github.io/world-currency-converter/web/`.

> The graded C program is `src/main.c`; the web page is an extra demo of the same idea.
