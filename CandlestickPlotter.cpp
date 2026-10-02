#include "CandlestickPlotter.h"
#include <iostream>
#include <iomanip>
#include <cmath>
#include <tuple>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

//code part without assisstance START
// ANSI escape codes for colors that i used for the candlesticks
#define RED "\033[31m"
#define GREEN "\033[32m"
#define RESET "\033[0m"

//normalize a value for ploting to a scale
int normalize(double value, double min, double max, int scale) {
    double normalizedValue = (value - min) / (max - min) * scale;
    int result = std::round(normalizedValue); // Round to avoid off-by-one errors
    return result;
}

void CandlestickPlotter::plotCandlesticks(const std::vector<std::vector<std::string>>& ohlcData) {
    const int plotHeight = 50;        //  height of the plot
    const int candlestickSpacing = 8; // spacing for compactnesss
    const double bufferFactor = 0.1; // 10% buffer above max and below min

    if (ohlcData.empty()) {
        std::cerr << "No data to plot!\n";
        return;
    }

    // displayingg the OHLC table for referencce
    std::cout << "\n================= OHLC Table for plotting =================\n";
    std::cout << std::setw(12) << "Date"
              << std::setw(12) << "Open"
              << std::setw(12) << "High"
              << std::setw(12) << "Low"
              << std::setw(12) << "Close" << "\n";

    //print each row of OHLC data
    for (const auto& row : ohlcData) {
        std::cout << std::setw(12) << row[0]
                  << std::setw(12) << std::fixed << std::setprecision(3) << row[1]
                  << std::setw(12) << row[2]
                  << std::setw(12) << row[3]
                  << std::setw(12) << row[4] << "\n";
    }
    std::cout << "===============================================\n";

    double globalHigh = -std::numeric_limits<double>::infinity();
    double globalLow = std::numeric_limits<double>::infinity();
//code part without assisstance END 


//code with a little teachers assisstance START
    // Calculate global min and max
    for (const auto& row : ohlcData) {
        double high = std::stod(row[2]);
        double low = std::stod(row[3]);
        globalHigh = std::max(globalHigh, high);
        globalLow = std::min(globalLow, low);
    }

    // add buffer to ensure the plot looks nicee
    double range = globalHigh - globalLow;
    if (range == 0) range = 1;
    double buffer = range * bufferFactor;
    globalHigh += buffer;
    globalLow -= buffer;

    // normalize candlestick positions for plotting
    std::vector<std::tuple<int, int, int, int>> normalizedCandlesticks;
    for (const auto& row : ohlcData) {
        double open = std::stod(row[1]);
        double high = std::stod(row[2]);
        double low = std::stod(row[3]);
        double close = std::stod(row[4]);

        int highPos = normalize(high, globalLow, globalHigh, plotHeight);
        int lowPos = normalize(low, globalLow, globalHigh, plotHeight);
        int openPos = normalize(open, globalLow, globalHigh, plotHeight);
        int closePos = normalize(close, globalLow, globalHigh, plotHeight);

        normalizedCandlesticks.emplace_back(highPos, lowPos, openPos, closePos);
    }

    // generating the candlestick plotting thrugh a loop
    std::cout << "\n=============== Plotting the Candlestick===============\n";
    for (int i = plotHeight; i >= 0; --i) {
        // label the yaxis with the corespondingg values
        double labelValue = globalLow + (globalHigh - globalLow) * i / plotHeight;
        std::cout << std::setw(6) << std::fixed << std::setprecision(1) << labelValue << " |";

        for (size_t j = 0; j < ohlcData.size(); ++j) {
            auto [highPos, lowPos, openPos, closePos] = normalizedCandlesticks[j];
            bool isUpward = closePos > openPos; // True if green candlestick

            std::string color = isUpward ? GREEN : RED;

            // spacinfg out the candlesticks and aligning  them above their corresponding date
            if (j > 0) {
                std::cout << std::string(candlestickSpacing - 4, ' '); // Adjust spacing for alignment
            }

            // rendering body (Open to Close) of the candlestick
            if (i <= std::max(openPos, closePos) && i >= std::min(openPos, closePos)) {
                std::cout << color << " ███  " << RESET;
            }
            //rrendering the wick (High to Low) out of body area
            else if (i <= highPos && i > lowPos) {
                std::cout << color << "  │   " << RESET;
            }
            //rendering  the empty space
            else {
                std::cout << "      ";
            }
        }
        std::cout << "\n";
    }
// code with a little teachers assisstance STOP


    //draw X-axis
    std::cout << "       +";
    for (size_t j = 0; j < ohlcData.size(); ++j) {
        std::cout << std::string(candlestickSpacing, '-'); // proper alignment for X-axis
    }
    std::cout << "\n";

    // draw X-axis labels with reduce gap b/w them
    std::cout << "       ";
    for (size_t j = 0; j < ohlcData.size(); ++j) {
        std::string shortDate = ohlcData[j][0].substr(2, 8); // formatingg to "YY-MM-DD"
        std::cout << std::string(candlestickSpacing - 6, ' ') << shortDate; // alignn labels
    }
    std::cout << "\n";
}
