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

class CSVParser {
public:
    bool loadCSV(const std::string &filename);
    vector<vector<string>> getData() const;
protected:
    vector<vector<string>> data;
};

#endif //CSVPARSER_H
