//
// Created by deniz on 3/21/2025.
//

#include "ReadFromFile.h"

#include "../cli/CLI.h"
#include "../cli/CommandRegistry.h"


void ReadFromFile::execute(Context *context, std::vector<std::string> args) {
    try {
        const auto registry = context->get<CommandRegistry*>("registry");
        if (args.size() != 3) {
            if (args.size() == 2) {
                cout << "Correct usage --> read_from_file <input> <output>, missing output." << endl;
                return;
            } if (args.size() == 1) {
                cout << "Correct usage --> read_from_file <input> <output>, missing input and output." << endl;
            }
        } else {
            CLI::runFromFile(*registry,args[1],args[2]);
        }
    } catch (...) {
        cout << "Error getting registry from context." << endl;
    }
}
