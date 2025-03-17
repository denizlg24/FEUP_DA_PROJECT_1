//
// Created by deniz on 3/17/2025.
//
#include <string.h>

#include "csv_parser/CSVParser.h"
#include "data_structures/MapFactory.h"
int main() {
    MapFactory factory;
    Map* map = factory.getMap();
    printf("Pointer to new map = %p\n",map);
    CSVParser csv_parser;
    string filename = "data/Locations.csv";
    vector<CityInfo> city_infos;
    if (csv_parser.loadCSV(filename)) {
        for (const auto& line: csv_parser.getData()) {
            if (line.size() == 4) {
                CityInfo newCity{};
                string parkingString = "1";
                newCity.id = stoi(line[1]);
                newCity.location = line[2];
                newCity.name = line[0];
                newCity.parking = line[3] == "1";
                city_infos.push_back(newCity);
            }
        }
    } else {
        std::cerr << "Failed to load CSV file." << std::endl;
    }
    factory.addCities(city_infos);
    printf("City Count = %llu\n",map->getCityCount());
    string newFilename = "data/Distances.csv";
    vector<RoadInfo> road_infos;
    if (csv_parser.loadCSV(newFilename)) {
        for (const auto& line: csv_parser.getData()) {
            if (line.size() == 4) {
                RoadInfo newRoad{};
                string noKey = "X";
                newRoad.source = factory.getMap()->getCity(line[0]);
                newRoad.dest = factory.getMap()->getCity(line[1]);
                newRoad.drivingWeight = line[2] == noKey ? 0 : stoi(line[2]);
                newRoad.walkingWeight = line[3] == noKey ? 0 : stoi(line[3]);
                newRoad.drivable = line[2] != noKey;
                newRoad.walkable = line[2] != noKey;
                road_infos.push_back(newRoad);
            }
        }
    } else {
        std::cerr << "Failed to load CSV file." << std::endl;
    }
    factory.addRoads(road_infos);
    printf("Road Count = %llu which is equal to %llu biderectional edges\n",map->getRoads().size(),map->getRoads().size()/2);
    return 0;
}
