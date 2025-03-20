//
// Created by Alex on 19/03/2025.
//

#include "dijkstra.h"
#include <unordered_map>
#include <queue>
#include <limits>
#include <algorithm>

vector<City *> dijkstra(const Map* map,City *start, City *end,
                                      const vector<int> &avoidNodes,
                                      const vector<pair<int, int>> &avoidSegments,double& weight,unordered_map<City *, double>& dist,bool driving) {
    unordered_map<City *, City *> prev;
    priority_queue<pair<double, City *>, vector<pair<double, City *>>, greater<>> pq;

    for (City *city : map->getCities()) {
        dist[city] = numeric_limits<double>::max();
    }
    dist[start] = 0;
    pq.emplace(0, start);
    while (!pq.empty()) {
        auto queue = pq.top();
        double currentDist = queue.first;
        City* current = queue.second;
        pq.pop();

        if (current == end) break;

        if (currentDist > dist[current]) continue;
        if (find(avoidNodes.begin(),avoidNodes.end(),current->getInfo().id)!=avoidNodes.end()) continue;

        for (Road *road : current->getAdj()) {
            City *neighbor = road->getDest();
            pair<int,int> segment1 = {current->getInfo().id,neighbor->getInfo().id};
            pair<int,int> segment2 = {neighbor->getInfo().id,current->getInfo().id};
            if (find(avoidSegments.begin(),avoidSegments.end(),segment1)!=avoidSegments.end() || find(avoidSegments.begin(),avoidSegments.end(),segment2)!=avoidSegments.end()) {
                continue;
            }
            if (driving && !road->isDrivable())continue;
            if (!driving && !road->isWalkable()) continue;
            double newWeight =driving ? road->getDrivingWeight() : road->getWalkingWeight();
            if (dist[current] + newWeight < dist[neighbor]) {
                dist[neighbor] = dist[current] + newWeight;
                prev[neighbor] = current;
                pq.emplace(dist[neighbor], neighbor);
            }
        }
    }

    vector<City *> path;
    if (dist[end] == numeric_limits<double>::max()) return path;
    weight = dist[end];
    for (City *at = end; at != nullptr; at = prev[at]) {
        path.push_back(at);
    }
    reverse(path.begin(), path.end());
    return path;
}