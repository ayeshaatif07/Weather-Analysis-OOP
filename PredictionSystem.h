#ifndef PREDICTION_SYSTEM_H
#define PREDICTION_SYSTEM_H

#include <vector>
#include <string>

//code part done with some teacher assistanccee

//class for predicting future temperature data
class PredictionSystem {
public:

    // predicts future temperatures based on historical OHLC data
    // takess the data, number of years to predict and moving average window size
    // Returns a 2D vector with predicted OHLC dataa
    std::vector<std::vector<std::string>> predictTemperature(
        const std::vector<std::vector<std::string>>& ohlcData,
        int yearsToPredict,
        int movingAverageWindow
    );
};

//function tto convert a year string to an integer
int yearToInt(const std::string& year);

#endif
