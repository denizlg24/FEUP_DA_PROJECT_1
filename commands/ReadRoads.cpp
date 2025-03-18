//
// Created by deniz on 3/18/2025.
//
#include "ReadRoads.h"

void ReadRoads::execute(Context *context, std::vector<std::string> args) {
    if (args.size() < 2) {
        cout << "Correct usage --> read_roads <filename>, missing filename." << endl;
        return;
    }
    try {
        auto* factory = context->get<MapFactory>("map_factory");
        const string& filename = args[1];
        cout << "Reading " << filename << "..." << endl;
        try {
            const vector<RoadInfo> road_infos = factory->readRoads(filename);
            cout << "Read " << road_infos.size() << " roads from " << filename << endl;
            cout << "Adding roads to map..." << endl;
            if (factory->addRoads(road_infos)) {
                cout << "Added roads to map!" << endl;
            } else {
                cout << "Couldn't add roads to map, try again please.!" << endl;
            }
        } catch (...){
            cout << "Couldn't read file "<< filename << ", try again please.!" << endl;
        }
    } catch (...) {
        cout << "Couldn't get MapFactory from context." << endl;
    }
}
