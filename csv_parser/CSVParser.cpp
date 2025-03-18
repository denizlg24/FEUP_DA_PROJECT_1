//
// Created by deniz on 3/17/2025.
//
#include "CSVParser.h"

bool CSVParser::loadCSV(const string &filename) {
    data = {};
    ifstream file(filename);
    if (!file.is_open()) {
        return false;
    }

    string line;
    bool isFirstLine = true;

    while (getline(file, line)) {
        vector<string> row;
        stringstream ss(line);
        string cell;

        while (getline(ss, cell, ',')) {
            row.push_back(cell);
        }

        if (isFirstLine) {
            // Ignore headers
            isFirstLine = false;
        } else {
            data.push_back(row);
        }
    }

    file.close();
    return true;
}

vector<vector<string> > CSVParser::getData() const {
    return data;
}
