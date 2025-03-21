//
// Created by deniz on 3/18/2025.
//
#include "HelpCommand.h"

void HelpCommand::execute(Context* context,std::vector<std::string> args) {
    cout << "===== HELP =====" << endl;
    cout << endl;
    cout << "help --> Displays a list of available commands." << endl;
    cout << endl;
    cout << "commands --> Displays a list of available commands." << endl;
    cout << endl;
    cout << "exit --> Exits program." << endl;
    cout << endl;
    cout << "read_cities <filename> --> Reads a csv file from filename and adds those cities as vertices to the map." << endl;
    cout << endl;
    cout << "read_roads <filename> --> Reads a csv file from filename and adds those roads as bidirectional edges to the map." << endl;
    cout << endl;
    cout << "plan_route [Mode:<mode>] [Source:<id>] [Destination:<id>] --> determines the best (fastest) route between a source and destination." << endl;
    cout << endl;
    cout << "restricted_route_planning [Mode:<mode>] [Source:<id>] [Destination:<id>] [AvoidNodes:<id>,<id>,...] [AvoidSegments:(id,id),(id,id),...] [IncludeNode:<id>] --> computes the fastest route with specific routing restrictions." << endl;
    cout << endl;
    cout << "environmental_route [Mode:<mode>] [Source:<id>] [Destination:<id>] [MaxWalkTime:<int>] [AvoidNodes:<id>,<id>,...] [AvoidSegments:(id,id),(id,id),...] --> plan a route that combines driving and walking efficiently." << endl;
    cout << endl;
    cout << "read_from_file <input> <output> --> Reads commands from <input> and places results inside <output>" << endl;
}