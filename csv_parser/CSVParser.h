//
// Created by deniz on 3/17/2025.
//

#ifndef CSVPARSER_H
#define CSVPARSER_H
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
using namespace std;

/// @class CSVParser
/// @brief A simple CSV file parser that loads and retrieves data.
class CSVParser {
public:
    /// @brief Loads a CSV file and stores its contents.
    /// @param filename The name of the CSV file to load.
    /// @return True if the file was successfully loaded, false otherwise.
    bool loadCSV(const std::string &filename);
    /// @brief Retrieves the parsed CSV data.
    /// @return A vector of rows, where each row is a vector of strings representing columns.
    vector<vector<string>> getData() const;
protected:
    vector<vector<string>> data;
};

#endif //CSVPARSER_H
