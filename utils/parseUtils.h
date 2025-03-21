//
// Created by Alex on 19/03/2025.
//

#ifndef PARSEINPUT_H
#define PARSEINPUT_H

#include <unordered_map>
#include <vector>
#include <string>

using namespace std;

/**
 * @brief Parses a segment string into a vector of integers.
 *
 * This function takes a string representing a segment separated by commas and limited by parenthesis
 * and parses it into a vector of integers.
 *
 * @param input A string representing the segments to be parsed.
 *
 * @return A vector of integers representing the parsed segments.
 */
vector<int> parseSegments(const string &input);
/**
 * @brief Parses a comma-separated string into a vector of integers.
 *
 * This function takes a string where the integers are separated by commas and parses it
 * into a vector of integers.
 *
 * @param input A string containing integers separated by commas.
 *
 * @return A vector of integers representing the parsed values.
 */
vector<int> parseCommaSeparated(const string &input);
/**
 * @brief Parses a vector of input lines into a mapping of strings to vectors of integers.
 *
 * This function processes a vector of strings, where each string represents a line of input.
 * It returns an unordered map where each key is a string, and the corresponding value is a vector
 * of integers parsed from the input lines.
 *
 * @param inputLines A vector of strings representing the input lines to be parsed.
 *
 * @return An unordered map where each key is a string, and each value is a vector of integers.
 */
unordered_map<string, vector<int>> parseInput(const vector<string> &inputLines);

#endif //PARSEINPUT_H
