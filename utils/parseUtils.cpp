//
// Created by Alex on 19/03/2025.
//

#include "parseUtils.h"

#include <algorithm>
#include <sstream>

vector<int> parseSegments(const string &input) {
    vector<int> result;
    stringstream ss(input);
    string segment;

    while (getline(ss, segment, ')')) {
        if (segment.empty()) continue;
        size_t start = segment.find('(');
        if (start != string::npos) {
            segment = segment.substr(start + 1);
        }

        stringstream segStream(segment);
        string num;
        while (getline(segStream, num, ',')) {
            if (!num.empty()) result.push_back(stoi(num));
        }
    }
    return result;
}

vector<int> parseCommaSeparated(const string &input) {
    vector<int> result;
    stringstream ss(input);
    string num;

    while (getline(ss, num, ',')) {
        if (!num.empty()) result.push_back(stoi(num));
    }
    return result;
}

unordered_map<string, vector<int>> parseInput(const vector<string> &inputLines) {
    unordered_map<string, vector<int>> parsedData;

    for (const string &line : inputLines) {
        size_t colonPos = line.find(':');
        if (colonPos == string::npos) continue;

        string key = line.substr(0, colonPos);
        string value = line.substr(colonPos + 1);

        key.erase(remove_if(key.begin(), key.end(), ::isspace), key.end());
        value.erase(remove_if(value.begin(), value.end(), ::isspace), value.end());



        if (key == "Mode") {
            if (value.empty()) {
                parsedData[key] = {};
                continue;
            }
            parsedData[key] = {value == "driving" ? 0 : 1};
        }
        else if (key == "Source" || key == "Destination" || key == "IncludeNode") {
            if (value.empty()) {
                parsedData[key] = {};
                continue;
            }
            parsedData[key] = {stoi(value)};
        }
        else if (key == "AvoidNodes") {
            if (value.empty()) {
                parsedData[key] = {};
                continue;
            }
            parsedData[key] = parseCommaSeparated(value);
        }
        else if (key == "AvoidSegments") {
            if (value.empty()) {
                parsedData[key] = {};
                continue;
            }
            parsedData[key] = parseSegments(value);
        } else if (key == "MaxWalkTime") {
            if (value.empty()) {
                parsedData[key] = {};
                continue;
            }
            parsedData[key] = {stoi(value)};
        }
    }

    return parsedData;
}
