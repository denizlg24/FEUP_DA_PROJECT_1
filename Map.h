//
// Created by deniz on 3/17/2025.
//

/**
 * @file city.h
 * @brief Defines the City, Road, and Map classes for representing a transportation network.
 */

#include <vector>
#include <string>
using namespace std;

#ifndef MAP_H
#define MAP_H

/**
 * @struct CityInfo
 * @brief Represents basic information about a city.
 */
struct CityInfo{
  int id;
  string location;
  string name;
  bool parking;

  /**
    * @brief Equality operator for CityInfo.
    * @param a Another CityInfo object.
    * @return True if all fields match, false otherwise.
   */
  inline bool operator==(CityInfo a) {
        if (a.id == id && a.location == location && a.name == name && a.parking == parking)
            return true;
        else
            return false;
  }
};

class Road;

/**
 * @class City
 * @brief Represents a city in the transportation network.
 */
class City{
public:
     /**
       * @brief Constructs a City object.
       * @param in City information.
     */
    City(CityInfo in);
    /**
     * @brief Retrieves the city's information.
     * @return The CityInfo object of the city.
     */
    CityInfo getInfo() const;
    /**
     * @brief Gets the adjacent roads of the city.
     * @return Vector of pointers to Road objects.
     */
    vector<Road*> getAdj() const;
    /**
     * @brief Checks if the city has been visited.
     * @return True if visited, false otherwise.
     */
    bool isVisited() const;
    /**
    * @brief Checks if the city is currently being processed.
    * @return True if processing, false otherwise.
    */
    bool isProcessing() const;
    /**
     * @brief Sets the city information.
     * @param info New CityInfo object.
     */
    void setInfo(CityInfo info);
    /**
    * @brief Sets the visited status of the city.
    * @param visited Boolean value to set.
    */
    void setVisited(bool visited);
    /**
     * @brief Sets the processing status of the city.
     * @param processing Boolean value to set.
     */
    void setProcessing(bool processing);
    /**
     * @brief Adds a road between two cities.
     * @param source Source city.
     * @param dest Destination city.
     * @param drivingWeight Weight of the road for driving.
     * @param walkingWeight Weight of the road for walking.
     * @return Pointer to the newly created Road object.
     */
    Road* addRoad(City * source, City * dest, double drivingWeight, double walkingWeight);

protected:
    CityInfo info;
    vector<Road*> adj;
    bool visited = false;
    bool processing = false;
};

/**
 * @class Road
 * @brief Represents a road connecting two cities.
 */
class Road{
public:
    /**
       * @brief Constructs a Road object.
       * @param source Source city.
       * @param dest Destination city.
       * @param drivingWeight Driving weight of the road.
       * @param walkingWeight Walking weight of the road.
       */
    Road(City * source, City * dest, double drivingWeight, double walkingWeight);
    /**
     * @brief Gets the origin city of the road.
     * @return Pointer to the origin City object.
     */
    City* getOrigin() const;
    /**
     * @brief Gets the destination city of the road.
     * @return Pointer to the destination City object.
     */
    City* getDest() const;
    /**
     * @brief Gets the driving weight of the road.
     * @return Driving weight as a double.
     */
    double getDrivingWeight() const;
    /**
   * @brief Gets the walking weight of the road.
   * @return Walking weight as a double.
   */
    double getWalkingWeight() const;
    /**
     * @brief Sets the reverse road for bidirectional connections.
     * @param reverse Pointer to the reverse Road object.
     */
    void setReverse(Road* reverse);
    /**
     * @brief Gets the reverse road for bidirectional connections.
     * @return Pointer to the reverse Road object.
     */
    Road* getReverse() const;
protected:
    City *orig;
    City *dest;
    Road* reverse;
    double drivingWeight;
    double walkingWeight;
};


/**
 * @class Map
 * @brief Represents a collection of cities and roads.
 */
class Map {
public:
    /**
       * @brief Finds a city in the map.
       * @param in CityInfo of the city to find.
       * @return Pointer to the City object if found, nullptr otherwise.
       */
    City *findCity(const CityInfo &in) const;
    /**
    * @brief Adds a new city to the map.
    * @param in CityInfo of the city to add.
    * @return True if the city was added successfully, false if it already exists.
    */
    bool addCity(const CityInfo &in);
    /**
    * @brief Adds a road between two cities.
    * @param source Source city information.
    * @param dest Destination city information.
    * @param drivingWeight Driving weight of the road.
    * @param walkingWeight Walking weight of the road.
    * @return True if the road was added successfully, false otherwise.
    */
    bool addRoad(const CityInfo &source, const CityInfo &dest, double drivingWeight, double walkingWeight);
    /**
    * @brief Gets the number of cities in the map.
    * @return The number of cities.
    */
    int getCityCount() const;
    /**
   * @brief Gets the list of cities in the map.
   * @return Vector of pointers to City objects.
   */
    vector<City *> getCities() const;
    /**
    * @brief Gets the list of roads in the map.
    * @return Vector of pointers to Road objects.
    */
    vector<Road *> getRoads() const;
protected:
    vector<City*> cities;
    vector<Road*> roads;
};

/************************* Road **************************/

Road::Road(City * source, City * dest, double drivingWeight, double walkingWeight): orig(source),dest(dest),drivingWeight(drivingWeight),walkingWeight(walkingWeight){}

void Road::setReverse(Road* rev){
   this->reverse = rev;
}

Road* Road::getReverse() const{
    return this->reverse;
}

City* Road::getOrigin() const{
  return this->orig;
}

City* Road::getDest() const{
  return this->dest;
}

double Road::getDrivingWeight() const{
  return this->drivingWeight;
}

double Road::getWalkingWeight() const{
    return this->walkingWeight;
}

/************************* City **************************/

City::City(CityInfo in): info(in) {};

void City::setInfo(CityInfo in){
    this->info = in;
};

CityInfo City::getInfo() const {
    return this->info;
}

void City::setVisited(bool vi) {
    this->visited = vi;
}

void City::setProcessing(bool pro) {
    this->processing = pro;
}

vector<Road*> City::getAdj() const {
    return this->adj;
}

bool City::isVisited() const {
    return this->visited;
}

bool City::isProcessing() const {
    return this->processing;
}

Road* City::addRoad(City * source, City * dest, double drivingWeight, double walkingWeight) {
    auto newRoad = new Road(source,dest,drivingWeight,walkingWeight);
    this->adj.push_back(newRoad);
    return newRoad;
}

/************************* Map **************************/

City* Map::findCity(const CityInfo &in) const{
    for(auto city: cities){
      if(city->getInfo() == in){
          return city;
      }
    }
    return nullptr;
}

bool Map::addCity(const CityInfo &in) {
    if (findCity(in) != nullptr)
        return false;
    cities.push_back(new City(in));
    return true;
}

bool Map::addRoad(const CityInfo &source, const CityInfo &dest, double drivingWeight, double walkingWeight){
    auto v1 = findCity(source);
    auto v2 = findCity(dest);
    if (v1 == nullptr || v2 == nullptr)
        return false;
    auto e1 = v1->addRoad(v1, v2, drivingWeight, walkingWeight);
    auto e2 = v2->addRoad(v2, v1, drivingWeight, walkingWeight);
    e1->setReverse(e2);
    e2->setReverse(e1);
    roads.push_back(e1);
    roads.push_back(e2);
    return true;
}

int Map::getCityCount() const{
  return this->cities.size();
}

vector<City*> Map::getCities() const{
  return this->cities;
}

vector<Road*> Map::getRoads() const{
    return this->roads;
}

#endif //MAP_H
