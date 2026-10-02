#include "CSVReader.h"
#include <fstream>
#include <sstream>
#include <iostream>

// constructor 
CSVReader::CSVReader() {}

// tokenize a CSV line based on a separator
std::vector<std::string> CSVReader::tokenise(const std::string& csvLine, char separator) {
    std::vector<std::string> tokens;
    std::stringstream ss(csvLine);
    std::string token;

    while (std::getline(ss, token, separator)) {
        tokens.push_back(token);
    }

    return tokens;
}

//readd CSV file andd returns it as a 2D vector
std::vector<std::vector<std::string>> CSVReader::readCSV(const std::string& inputFile) {
    std::ifstream csvFile(inputFile);
    std::vector<std::vector<std::string>> data;
    std::string line;

    if (!csvFile.is_open()) {
        std::cerr  << "Could not open the file: " << inputFile << std::endl;
        return data;
    }

    while (std::getline(csvFile, line)) {
        data.push_back(tokenise(line, ',')); //adjust separator if needed
    }

    csvFile.close();
    return data;
}

//extract country codes from header of CSV
std::vector<std::string> CSVReader::getCountries(const std::vector<std::string>& header) {
    std::vector<std::string> countries;
    for (const auto& col : header) {
        if (col.find("_temperature") != std::string::npos) {
            countries.push_back(col.substr(0, col.find("_temperature")));
        }
    }
    return countries;
}

//this part of code was written without assisstance