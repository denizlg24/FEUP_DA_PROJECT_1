//
// Created by deniz on 3/17/2025.
//

#ifndef MAPFACTORY_H
#define MAPFACTORY_H

#include "Map.h"
#include "CSVParser.h"

class MapFactory {
public:
    MapFactory();
    void setMap(Map* map);
    Map* getMap() const;
    vector<RoadInfo> readRoads(const string &filename) const;
    static vector<CityInfo> readCities(const string& filename);
    bool addCities(const vector<CityInfo>& cities);
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
        newRoad.walkable = line[2] != noKey;
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
