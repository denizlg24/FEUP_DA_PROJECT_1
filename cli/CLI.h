//
// Created by deniz on 3/18/2025.
//

#ifndef CLI_H
#define CLI_H
#include "CommandRegistry.h"
#include <string>
using namespace std;

class CLI {
public:
    static void runInteractive(CommandRegistry& registry);
    static void runFromFile(CommandRegistry& registry, const string& inputFile, const string& outputFile);
};



#endif //CLI_H
