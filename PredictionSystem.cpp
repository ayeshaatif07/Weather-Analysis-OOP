
#include "PredictionSystem.h"
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <algorithm>

// part of code done a a little assistancee START
// function that helpss to convert a year string to an integer
int yearToInt(const std::string& year) {
    return std::stoi(year);
}

//function that helps to to create a year string from an integer
std::string intToYear(int year) {
    return std::to_string(year);
}

//predicts future temperature data based on previouss OHLC data
std::vector<std::vector<std::string>> PredictionSystem::predictTemperature(
    const std::vector<std::vector<std::string>>& historicalOHLC, 
    int yearsToPredict, 
    int movingAverageWindow
) {
    std::vector<std::vector<std::string>> predictedData;

    // Initialize with the last year of historical data
    auto lastRow = historicalOHLC.back();
    double lastClose = std::stod(lastRow[4]);

    // initialize sums for calculating averages
    double sumOpen = 0.0, sumHigh = 0.0, sumLow = 0.0, sumClose = 0.0;
    int count = historicalOHLC.size();

    for (const auto& row : historicalOHLC) {
        sumOpen += std::stod(row[1]);
        sumHigh += std::stod(row[2]);
        sumLow += std::stod(row[3]);
        sumClose += std::stod(row[4]);
    }
    // part of code done a a little assistancee END


// calculated the mean avg w/out assistance
    //predicting for future years
    int startYear = std::stoi(lastRow[0]);
    for (int i = 1; i <= yearsToPredict; ++i) {
        double predictedOpen = lastClose;
        double predictedHigh = sumHigh / count;
        double predictedLow = sumLow / count;
        double predictedClose = sumClose / count;

        //adding predicted data for the current year
        predictedData.push_back({
            std::to_string(startYear + i),
            std::to_string(predictedOpen),
            std::to_string(predictedHigh),
            std::to_string(predictedLow),
            std::to_string(predictedClose)
        });

        //update cumulative sums and count
        sumOpen += predictedOpen;
        sumHigh += predictedHigh;
        sumLow += predictedLow;
        sumClose += predictedClose;
        count++;
        
        //Update lastClose for continuity
        lastClose = predictedClose;
    }

    return predictedData;
}
