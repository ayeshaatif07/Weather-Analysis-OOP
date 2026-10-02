#include "OHLCComputer.h"
#include <map>
#include <algorithm>
#include <numeric>
#include <iomanip>
#include <iostream>
#include <sstream>

// function that help s to extract date from UTC timestamp
std::string extractDate(const std::string& utcTimestamp) {
    return utcTimestamp.substr(0, 10); // Extract "YYYY-MM-DD"
}

//  function that helps to create group keys based on resolution
std::string createGroupKey(const std::string& date, const std::string& resolution) {
    if (resolution == "daily") {
        return date; // YYYY-MM-DD
    } else if (resolution == "monthly") {
        return date.substr(0, 7); // YYYY-MM
    } else if (resolution == "yearly") {
        return date.substr(0, 4); // YYYY
    }
    return date; // default to daily if the resolution is invalid
}

//helper function to Check if  date is within the specified start and end date range
bool isWithinRange(const std::string& date, const std::string& startDate, const std::string& endDate) {
    return date >= startDate && date <= endDate;
}

// calculates OHLC (Open, High, Low, Close) data for the given country and resolution
std::vector<std::vector<std::string>> OHLCComputer::calculateOHLC(
    const std::vector<std::vector<std::string>>& data, 
    const std::string& countryCode,
    const std::string& resolution,
    const std::string& startDate,
    const std::string& endDate
) {
    std::map<std::string, std::vector<double>> groupedTemperatures;

// this identifiess the column index for the target country temperature data
    size_t countryColIndex = 0;
    const auto& header = data[0];
    std::string targetColumn = countryCode + "_temperature";
    for (size_t i = 0; i < header.size(); ++i) {
        if (header[i] == targetColumn) {
            countryColIndex = i;
            break;
        }
    }

    // Group tempp data by resolution (daily, monthly, yearly)
    for (size_t i = 1; i < data.size(); ++i) {
        const std::string& utcTimestamp = data[i][0];
        std::string date = extractDate(utcTimestamp);

        double temp = std::stod(data[i][countryColIndex]);
        std::string groupKey = createGroupKey(date, resolution);

        if (date < startDate) {
            groupedTemperatures[groupKey].push_back(temp); // Store temps before startDate for prevClose
        } else if (isWithinRange(date, startDate, endDate)) {
            groupedTemperatures[groupKey].push_back(temp);
        }
    }

    // find the last Close value before the startDate
    double prevClose = 0.0;
    for (const auto& [key, temps] : groupedTemperatures) {
        if (key < startDate) {
            prevClose = std::accumulate(temps.begin(), temps.end(), 0.0) / temps.size();
        }
    }

    std::vector<std::vector<std::string>> ohlcData;

    //generating OHLC data for the specified range
    for (const auto& [key, temps] : groupedTemperatures) {
        if (key < startDate || key > endDate) continue;

        double high = *std::max_element(temps.begin(), temps.end());
        double low = *std::min_element(temps.begin(), temps.end());
        double close = std::accumulate(temps.begin(), temps.end(), 0.0) / temps.size();
        double open = (prevClose == 0.0) ? close : prevClose; // Use prevClose or default to close

        ohlcData.push_back({
            key, 
            std::to_string(open),
            std::to_string(high),
            std::to_string(low),
            std::to_string(close)
        });

        prevClose = close; // update previous close for the next group
    }

    return ohlcData;
}
