//
// Created by deniz on 3/18/2025.
//
#include "HelpCommand.h"

void HelpCommand::execute(Context* context,std::vector<std::string> args) {
    cout << "===== HELP =====" << endl;
    cout << "help --> Displays a list of available commands." << endl;
    cout << "commands --> Displays a list of available commands." << endl;
    cout << "exit --> Exits program." << endl;
    cout << "read_cities <filename> --> Reads a csv file from filename and adds those cities as vertices to the map." << endl;
    cout << "read_roads <filename> --> Reads a csv file from filename and adds those roads as bidirectional edges to the map." << endl;
}