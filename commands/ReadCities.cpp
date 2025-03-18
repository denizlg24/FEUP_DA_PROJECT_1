//
// Created by deniz on 3/18/2025.
//
#include "ReadCities.h"

void ReadCities::execute(Context *context, std::vector<std::string> args) {
    if (args.size() < 2) {
        cout << "Correct usage --> read_cities <filename>, missing filename." << endl;
        return;
    }
    try {
        auto* factory = context->get<MapFactory>("map_factory");
        const string& filename = args[1];
        cout << "Reading " << filename << "..." << endl;
        try {
            const vector<CityInfo> city_infos = MapFactory::readCities(filename);
            cout << "Read " << city_infos.size() << " cities from " << filename << endl;
            cout << "Adding cities to map..." << endl;
            if (factory->addCities(city_infos)) {
                cout << "Added cities to map!" << endl;
            } else {
                cout << "Couldn't add cities to map, try again please.!" << endl;
            }
        } catch (...){
            cout << "Couldn't read file "<< filename << ", try again please!" << endl;
        }
    } catch (...) {
        cout << "Couldn't get MapFactory from context." << endl;
    }
}
