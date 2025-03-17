//
// Created by deniz on 3/17/2025.
//

#ifndef MAPFACTORY_H
#define MAPFACTORY_H

#include "Map.h"


class MapFactory {
public:
    MapFactory();
    void setMap(Map* map);
    Map* getMap() const;
    bool addCities(vector<CityInfo> cities);
    bool addRoads(vector<RoadInfo> roads);
protected:
    Map* map;
};

MapFactory::MapFactory() {
  Map* newMap = new Map();
  setMap(newMap);
}

void MapFactory::setMap(Map* m){
  this->map = m;
}

Map* MapFactory::getMap() const{
  return this->map;
}

bool MapFactory::addCities(vector<CityInfo> cities){
  Map* m = getMap();
  for(auto city: cities){
    if(!m->addCity(city)){
      setMap(nullptr);
      return false;
    }
  }
  return true;
}

bool MapFactory::addRoads(vector<RoadInfo> roads){
  Map* m = getMap();
  for(auto road: roads){
    if(!m->addRoad(road)){
      setMap(nullptr);
      return false;
    }
  }
  return true;
}

#endif //MAPFACTORY_H
