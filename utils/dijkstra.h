//
// Created by Alex on 19/03/2025.
//

#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include <unordered_map>
#include <vector>
#include "../data_structures/Map.h"

using namespace std;

vector<City *> dijkstra(const Map* map,City *start, City *end,
                                      const vector<int> &avoidNodes,
                                      const vector<pair<int, int>> &avoidSegments,double& weight,unordered_map<City *, double>& dist,bool driving = true);

#endif //DIJKSTRA_H
