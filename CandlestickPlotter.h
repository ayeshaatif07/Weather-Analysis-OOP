#ifndef CANDLESTICK_PLOTTER_H
#define CANDLESTICK_PLOTTER_H

#include <vector>
#include <string>

// This class is responsible for plotting candlestick charts
class CandlestickPlotter {
public:
    // Constructor of plotting the candlestick chart
    void plotCandlesticks(const std::vector<std::vector<std::string>>& ohlcData);
};

#endif

// this part of code is written without assisstance 