//
// Created by Alex on 19/03/2025.
//

#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include <unordered_map>
#include <vector>
#include "../data_structures/Map.h"

using namespace std;
/**
* @brief Computes the shortest path between two cities using Dijkstra's algorithm.
*
* This function finds the shortest path from the starting city to the destination city
* in a map, while optionally avoiding specified nodes and segments. The function will
* return the total weight of the path and update the distances for each city along the way.
*
* @param map A pointer to the Map object containing the cities and their connections.
* @param start A pointer to the starting City.
* @param end A pointer to the destination City.
* @param avoidNodes A vector of city indices to avoid during the pathfinding process.
* @param avoidSegments A vector of pairs representing segments (edges) to avoid.
* @param weight A reference to a variable where the total weight (distance) of the shortest path will be stored.
* @param dist A reference to an unordered_map that will hold the shortest distances from the start city to each city.
* @param driving A boolean flag indicating if the pathfinding is for driving (default is true).
*
* @return A vector of pointers to the cities that form the shortest path.
**/
vector<City *> dijkstra(const Map* map,City *start, City *end,
                                      const vector<int> &avoidNodes,
                                      const vector<pair<int, int>> &avoidSegments,double& weight,unordered_map<City *, double>& dist,bool driving = true);

#endif //DIJKSTRA_H
