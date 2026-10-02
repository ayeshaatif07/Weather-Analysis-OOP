#include "CSVReader.h"
#include "OHLCComputer.h"
#include "CandlestickPlotter.h"
#include "PredictionSystem.h"
#include <iostream>
#include <iomanip>
#include <limits>
#include <string>


// code part without assisstance START
// displayingg the main menu in the start 
void displayMainMenu() {
    std::cout << "\n========== WEATHER ANALYSIS DATA IMPLEMENTATIONS ==========\n";
    std::cout << "1. View the filtered OHLC table and Candlestick plot \n";
    std::cout << "2. Prediction (Task 4)\n";
    std::cout << "0. Exit\n";
    std::cout << "======================================\n";
}

//displaying the country sellection menu
void displayMenu(const std::vector<std::string>& countries) {
    std::cout << "\n========== Countries To Choose From==========\n";
    for (size_t i = 0; i < countries.size(); ++i) {
        std::cout << i + 1 << ". " << countries[i] << "\n";
    }
    std::cout << "0. Back\n";
    std::cout << "==========================================\n";
}

//here display the resolution menu 
void displayResolutionMenu() {
    std::cout << "\n========== Select the Time Resolution ==========\n";
    std::cout << "1. Daily\n";
    std::cout << "2. Monthly\n";
    std::cout << "3. Yearly\n";
    std::cout << "0. Go Back\n";
    std::cout << "===========================================\n";
}

//Clear input buffer to handle invalid user input
void clearInput() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// Get valid input from the userr
int getValidInput(int min, int max) {
    int choice;
    while (true) {
        std::cin >> choice;
        if (std::cin.fail() || choice < min || choice > max) {
            std::cout << "Invalid input. Please enter a number between " << min << " and " << max << ": ";
            clearInput();
        } else {
            break;
        }
    }
    return choice;
}

//CODE PART WITHOUT ASSISTANCE END



//this part of code below needed some asssistance, the main function as creating the main menu was a bit tricky
//the main functionn
int main() {
    
      // Initialize required classes
    CSVReader reader;
    OHLCComputer ohlcComputer;
    CandlestickPlotter plotter;
    PredictionSystem predictor;
    std::string inputFile = "weather_data_EU_1980-2019_temp_only.csv";

    //reading the CSV data
    auto data = reader.readCSV(inputFile);
    if (data.empty()) {
        std::cerr << "Error: Unable to read the file: " << inputFile << std::endl;
        return 1;
    }

    //extracting the countries from the header
    const auto& header = data[0];
    auto countries = reader.getCountries(header);

    while (true) {
        displayMainMenu();
        std::cout << "Select an option: ";
        int mainChoice = getValidInput(0, 2);

        if (mainChoice == 0) {
            std::cout << "Exiting program.. Goodbye!\n";
            break;
        }
        //displaying main menu and handling user choice
        displayMenu(countries);
        std::cout << "Select a country by number (or 0 to go back): ";
        int countryChoice = getValidInput(0, countries.size());
        if (countryChoice == 0) {
            continue;
        }

        std::string selectedCountry = countries[countryChoice - 1];
        std::cout << "\nYou selected: " << selectedCountry << "\n";

        if (mainChoice == 1) {
             // viewing OHLC data  and candlestick plottingg
            while (true) {
                displayResolutionMenu();
                std::cout << "Select a resolution by number (or 0 to go back): ";
                int resolutionChoice = getValidInput(0, 3);
                if (resolutionChoice == 0) {
                    break;
                }

                std::string resolution;
                if (resolutionChoice == 1) resolution = "daily";
                else if (resolutionChoice == 2) resolution = "monthly";
                else resolution = "yearly";

                std::string startDate, endDate;
                std::cout << "Enter the start date (YYYY-MM-DD): ";
                std::cin >> startDate;
                std::cout << "Enter the end date (YYYY-MM-DD): ";
                std::cin >> endDate;

                auto ohlcData = ohlcComputer.calculateOHLC(data, selectedCountry, resolution, startDate, endDate);
                if (ohlcData.empty()) {
                    std::cout << "No OHLC data available for " << selectedCountry << " within the specified date range.\n";
                } else {
                    std::cout << "\nOHLC Data (" << resolution << ") for " << selectedCountry << ":\n";
                    plotter.plotCandlesticks(ohlcData);
                }
            }
        } else if (mainChoice == 2) {
            //predicting task 
            std::cout << "\n========== Predict Weather ==========\n";

            // predict for yearly resolution starting from 2020
            auto ohlcData = ohlcComputer.calculateOHLC(data, selectedCountry, "yearly", "1980-01-01", "2019-12-31");
            if (ohlcData.empty()) {
                std::cout << "No data available for " << selectedCountry << "\n";
                continue;
            }

            std::cout << "Enter the number of future years to predict: ";
            int yearsToPredict = getValidInput(1, 10);

            int movingAverageWindow = static_cast<int>(ohlcData.size() / 5);
            if (movingAverageWindow == 0) movingAverageWindow = 1;

            auto predictionData = predictor.predictTemperature(ohlcData, yearsToPredict, movingAverageWindow);

            std::cout << "\nPredicted OHLC Data for " << selectedCountry << ":\n";

            // Plot predicted data
            plotter.plotCandlesticks(predictionData);
        }
    }

    return 0;
}
