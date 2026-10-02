# Weather Analysis

A C++ command-line application for the Object Oriented Programming midterm. It reads hourly European temperature data (1980–2019), turns it into OHLC (Open, High, Low, Close) values, shows candlestick-style plots in the terminal, and predicts future yearly temperatures.

## Features

- Choose from the countries found in the dataset.
- Compute OHLC temperature data at **daily**, **monthly** or **yearly** resolution for a custom date range.
- Plot the OHLC data as a text candlestick chart.
- Predict temperatures for the next 1–10 years using a moving average.

## Project Structure

| File | Purpose |
|------|---------|
| `main.cpp` | Menus, user input handling and program flow |
| `CSVReader.h/.cpp` | Reads the CSV file and extracts the country list |
| `OHLCComputer.h/.cpp` | Groups temperatures by resolution and computes OHLC |
| `CandlestickPlotter.h/.cpp` | Draws the candlestick chart in the terminal |
| `PredictionSystem.h/.cpp` | Predicts future OHLC data from historical data |
| `OOP REPORT MID.pdf` | Project report |
| `OOP CODE PDF.pdf` | Printable copy of the code |

## Dataset

The program expects `weather_data_EU_1980-2019_temp_only.csv` in the working directory. It has an `utc_timestamp` column followed by one `<COUNTRY>_temperature` column per country. The file (about 70 MB) is included in the repository root.

## Build and Run

Requires a C++11 (or newer) compiler such as `g++` or `clang++`.

```bash
g++ -std=c++17 -o weather_analysis main.cpp CSVReader.cpp OHLCComputer.cpp CandlestickPlotter.cpp PredictionSystem.cpp
./weather_analysis
```

## Usage

1. Pick **1** for the OHLC table and candlestick plot, or **2** for prediction.
2. Select a country by number.
3. For option 1, choose a resolution and enter start and end dates as `YYYY-MM-DD` (for example `1990-01-01` to `1990-12-31`).
4. For option 2, enter how many future years to predict (1–10).
5. Enter `0` to go back or exit.

## Author

Ayesha Atif — Semester 3, Object Oriented Programming midterm.
