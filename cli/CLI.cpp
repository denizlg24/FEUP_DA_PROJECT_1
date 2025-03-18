//
// Created by deniz on 3/18/2025.
//

#include "CLI.h"

#include <fstream>
#include <sstream>

void CLI::runInteractive(CommandRegistry& registry) {
    std::string input;
    while (true) {
        std::cout << "DA24/25 > ";
        std::getline(std::cin, input);
        if (input.empty()) continue;
        if (input == "exit" || input == "quit") break;

        std::istringstream iss(input);
        std::vector<std::string> tokens;
        std::string token;
        while (iss >> token) {
            tokens.push_back(token);
        }
        if (!tokens.empty()) {
            registry.executeCommand(tokens[0], tokens);
        }
    }
}

void CLI::runFromFile(CommandRegistry& registry, const string& inputFile, const string& outputFile) {
    ifstream in(inputFile);
    if (!in) {
        cerr << "Error: Cannot open input file " << inputFile << endl;
        return;
    }

    ofstream out(outputFile);
    if (!out) {
        cerr << "Error: Cannot open output file " << outputFile << endl;
        return;
    }

    streambuf* coutBackup = cout.rdbuf(out.rdbuf());

    string line;
    int lineNumber = 1;
    while (getline(in, line)) {
        istringstream iss(line);
        vector<string> tokens;
        string token;
        while (iss >> token) {
            tokens.push_back(token);
        }

        if (!tokens.empty()) {
            string commandName = tokens[0];

            auto it = registry.getCommands().find(commandName);
            if (it != registry.getCommands().end()) {
                try {
                    registry.getCommand(it->second)->execute(registry.getContext(),tokens);
                } catch (const exception& e) {
                    cerr << "Error on line " << lineNumber << ": " << e.what() << endl;
                }
            } else {
                cerr << "Error on line " << lineNumber << ": Unknown command '" << commandName << "'" << endl;
            }
        }

        lineNumber++;
    }

    cout.rdbuf(coutBackup);
}