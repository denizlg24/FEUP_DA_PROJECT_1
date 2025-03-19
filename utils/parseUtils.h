//
// Created by Alex on 19/03/2025.
//

#ifndef PARSEINPUT_H
#define PARSEINPUT_H

#include <unordered_map>
#include <vector>
#include <string>

using namespace std;

vector<int> parseSegments(const string &input);
vector<int> parseCommaSeparated(const string &input);
unordered_map<string, vector<int>> parseInput(const vector<string> &inputLines);

#endif //PARSEINPUT_H
