//
// Created by deniz on 3/18/2025.
//

#ifndef CLI_H
#define CLI_H
#include "CommandRegistry.h"
#include <string>
using namespace std;

/// @class CLI
/// @brief Handles command-line interaction and execution of commands from files.
class CLI {
public:
    /// @brief Runs the CLI, taking commands from standard input.
    /// @param registry Reference to the CommandRegistry that holds available commands.
    static void run(CommandRegistry& registry);
    /// @brief Executes commands from an input file and writes output to an output file.
    /// @param registry Pointer to the CommandRegistry containing available commands.
    /// @param inputFile Path to the input file containing commands.
    /// @param outputFile Path to the output file where results will be written.
    static void runFromFile(CommandRegistry* registry, const string& inputFile, const string& outputFile);
};



#endif //CLI_H
