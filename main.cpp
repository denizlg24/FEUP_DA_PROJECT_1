//
// Created by deniz on 3/17/2025.
//
#include <string.h>
#include "data_structures/MapFactory.h"
#include <stdio.h>
#include <string>

bool hasInsertedCities = false;

void process(std::string const & line,MapFactory factory) {
    istringstream iss(line);
    vector<std::string> tokens;
    string token;

    while (iss >> token) {
        tokens.push_back(token);
    }

    if (tokens.empty()) return;

    const std::string command = tokens[0];

    if (command == "read_cities") {
        if (tokens.size() < 2) {
            cout << "Correct usage --> read_cities <filename>, missing filename." << endl;
            return;
        }
        const string& filename = tokens[1];
        cout << "Reading " << filename << "..." << endl;
        try {
            const vector<CityInfo> city_infos = MapFactory::readCities(filename);
            cout << "Read " << city_infos.size() << " cities from " << filename << endl;
            cout << "Adding cities to map..." << endl;
            if (factory.addCities(city_infos)) {
                cout << "Added cities to map!" << endl;
                hasInsertedCities = true;
            } else {
                cout << "Couldn't add cities to map, try again please.!" << endl;
            }
        } catch (...){
            cout << "Couldn't read file "<< filename << ", try again please!" << endl;
        }
    } else if (command == "read_roads") {
        if (!hasInsertedCities) {
            cout << "Must read cities before reading roads, this would cause a memory access error." << endl;
            return;
        }
        if (tokens.size() < 2) {
            cout << "Correct usage --> read_roads <filename>, missing filename." << endl;
            return;
        }
        const string& filename = tokens[1];
        cout << "Reading " << filename << "..." << endl;
        try {
            const vector<RoadInfo> road_infos = factory.readRoads(filename);
            cout << "Read " << road_infos.size() << " roads from " << filename << endl;
            cout << "Adding roads to map..." << endl;
            if (factory.addRoads(road_infos)) {
                cout << "Added roads to map!" << endl;
            } else {
                cout << "Couldn't add roads to map, try again please.!" << endl;
            }
        } catch (...){
            cout << "Couldn't read file "<< filename << ", try again please.!" << endl;
        }
    }
    else if (command == "exit") {
        cout << "Exiting." << endl;
        exit(0);
    } else {
        cout << "===== HELP =====" << endl;
        cout << "help --> Displays a list of available commands." << endl;
        cout << "commands --> Displays a list of available commands." << endl;
        cout << "exit --> Exits program." << endl;
        cout << "read_cities <filename> --> Reads a csv file from filename and adds those cities as vertices to the map." << endl;
        cout << "read_roads <filename> --> Reads a csv file from filename and adds those roads as bidirectional edges to the map." << endl;
    }
};

int main() {
    MapFactory factory;
    for (string line; cout << "DA24/25 >" && getline(cin, line); )
    {
        if (!line.empty()) { process(line,factory); }
    }
    return 0;
}
