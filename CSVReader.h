#ifndef CSVREADER_H
#define CSVREADER_H

#include <vector>
#include <string>

//class to handle reading and thee processing of CSV data
class CSVReader {
public:
    CSVReader();
    std::vector<std::vector<std::string>> readCSV(const std::string& inputFile);
    std::vector<std::string> getCountries(const std::vector<std::string>& header);
    std::vector<std::vector<std::string>> calculateOHLC(const std::vector<std::vector<std::string>>& data, const std::string& countryCode);

private:
//thiss splits a CSV line into tokens based on a separator
    std::vector<std::string> tokenise(const std::string& csvLine, char separator);
};

#endif

//code part written without assistancee