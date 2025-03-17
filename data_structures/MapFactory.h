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
