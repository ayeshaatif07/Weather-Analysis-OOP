#ifndef OHLC_COMPUTER_H
#define OHLC_COMPUTER_H

#include <vector>
#include <string>

//calculating the  OHLC (Open, High, Low, Close) data from temperature records
class OHLCComputer {
public:

    // Calculates OHLC data for a country using the given data
    // Takes the country code, resolution (daily, monthly, yearly), start date and end date
    // Returns a 2D vector with OHLC data (date, open, high, low, close)
    std::vector<std::vector<std::string>> calculateOHLC(
        const std::vector<std::vector<std::string>>& data, 
        const std::string& countryCode,
        const std::string& resolution,
        const std::string& startDate,
        const std::string& endDate
    );
};

#endif

// this part of code was written without assistance
