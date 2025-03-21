//
// Created by deniz on 3/17/2025.
//

#ifndef MAPFACTORY_H
#define MAPFACTORY_H

#include "Map.h"
#include "../csv_parser/CSVParser.h"

/// @class MapFactory
/// @brief Handles the creation and management of maps, including loading city and road data from CSV files.
class MapFactory {
public:
  /// @brief Constructor that initializes the MapFactory with a new Map instance.
    MapFactory();
  /// @brief Sets the current map.
  /// @param map Pointer to a Map object.
    void setMap(Map* map);
  /// @brief Retrieves the current map.
  /// @return Pointer to the current Map object.
    Map* getMap() const;
  /// @brief Reads road data from a CSV file.
  /// @param filename The name of the CSV file containing road data.
  /// @return A vector of RoadInfo structures containing road information.
    vector<RoadInfo> readRoads(const string &filename) const;
  /// @brief Reads city data from a CSV file.
  /// @param filename The name of the CSV file containing city data.
  /// @return A vector of CityInfo structures containing city information.
    static vector<CityInfo> readCities(const string& filename);
  /// @brief Adds a list of cities to the current map.
  /// @param cities A vector of CityInfo objects representing the cities to be added.
  /// @return True if all cities were added successfully, false otherwise.
    bool addCities(const vector<CityInfo>& cities);
  /// @brief Adds a list of roads to the current map.
  /// @param roads A vector of RoadInfo objects representing the roads to be added.
  /// @return True if all roads were added successfully, false otherwise.
    bool addRoads(const vector<RoadInfo>& roads);
protected:
    Map* map = nullptr;
};

inline MapFactory::MapFactory() {
  auto newMap = new Map();
  setMap(newMap);
}

inline void MapFactory::setMap(Map* m){
  this->map = m;
}

inline Map* MapFactory::getMap() const{
  return this->map;
}

inline vector<CityInfo> MapFactory::readCities(const string& filename) {
  CSVParser csv_parser;
  if (csv_parser.loadCSV(filename)) {
    vector<CityInfo> city_infos;
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
    return city_infos;
  } else {
    __throw_runtime_error("Error opening file.");
  }
}

inline vector<RoadInfo> MapFactory::readRoads(const string& filename) const {
  CSVParser csv_parser;
  if (csv_parser.loadCSV(filename)) {
    vector<RoadInfo> road_infos;
    for (const auto& line: csv_parser.getData()) {
      if (line.size() == 4) {
        RoadInfo newRoad{};
        string noKey = "X";
        newRoad.source = getMap()->getCity(line[0]);
        newRoad.dest = getMap()->getCity(line[1]);
        newRoad.drivingWeight = line[2] == noKey ? 0 : stoi(line[2]);
        newRoad.walkingWeight = line[3] == noKey ? 0 : stoi(line[3]);
        newRoad.drivable = line[2] != noKey;
        newRoad.walkable = line[3] != noKey;
        road_infos.push_back(newRoad);
      }
    }
    return road_infos;
  } else {
    __throw_runtime_error("Error opening file.");
  }
}

inline bool MapFactory::addCities(const vector<CityInfo>& cities){
  Map* m = getMap();
  for(const auto& city: cities){
    if(!m->addCity(city)){
      setMap(nullptr);
      return false;
    }
  }
  return true;
}

inline bool MapFactory::addRoads(const vector<RoadInfo>& roads){
  Map* m = this->getMap();
  for(const auto& road: roads){
    if(!m->addRoad(road)){
      setMap(nullptr);
      return false;
    }
  }
  return true;
}

#endif //MAPFACTORY_H
