//
// Created by deniz on 3/20/2025.
//

#include "EnvironmentalRoute.h"

#include <limits>
#include <algorithm>
#include "../utils/parseUtils.h"
#include "../utils/dijkstra.h"



void EnvironmentalRoute::execute(Context *context, std::vector<std::string> args) {
    unordered_map<string, vector<int>> parsedArgs = parseInput(args);
    if (parsedArgs.find("Mode") == parsedArgs.end()) {
        cout << "Mode argument not provided." << endl;
        return;
    }
    if (parsedArgs.find("Source") == parsedArgs.end()) {
        cout << "Source argument not provided." << endl;
        return;
    }
    if (parsedArgs.find("Destination") == parsedArgs.end()) {
        cout << "Destination argument not provided." << endl;
        return;
    }
    if (parsedArgs.find("AvoidNodes") == parsedArgs.end()) {
        cout << "AvoidNodes argument not provided." << endl;
        return;
    }
    if (parsedArgs.find("AvoidSegments") == parsedArgs.end()) {
        cout << "AvoidSegments argument not provided." << endl;
        return;
    }
    if (parsedArgs.find("MaxWalkTime") == parsedArgs.end()) {
        cout << "MaxWalkTime argument not provided." << endl;
        return;
    }
    try {
        auto* factory = context->get<MapFactory>("map_factory");
        auto* map = factory->getMap();
        City *source = map->getCityById(parsedArgs["Source"][0]);
        City *destination = map->getCityById(parsedArgs["Destination"][0]);
        if (!source || !destination) {
            cout << "Source:" << parsedArgs["Source"][0] << endl;
            cout << "Destination:" << parsedArgs["Destination"][0] << endl;
            cout << "RestrictedDrivingRoute:None" << endl;
            return;
        };
        vector<pair<int,int>> avoidSegments = {};
        if (!parsedArgs["AvoidSegments"].empty()) {
            for (int i = 0; i < parsedArgs["AvoidSegments"].size() - 1; i+=2) {
                pair<int,int> segment = {parsedArgs["AvoidSegments"][i],parsedArgs["AvoidSegments"][i+1]};
                avoidSegments.push_back(segment);
            }
        }
        double weight = 0;
        double walkingWeight = 0;
        unordered_map<City*,double> dist;
        dijkstra(map,source, destination, parsedArgs["AvoidNodes"], avoidSegments,weight,dist);
        double bestTotalTime = numeric_limits<double>::max();
        City* bestParkingNode = nullptr;
        vector<City*> possibleParkingNodes;
        for (City* parkingNode : map->getCities()) {
            if (!parkingNode->getInfo().parking) continue;
            if (dist[parkingNode] == numeric_limits<double>::max()) continue;

            unordered_map<City*, double> walkingDist;
            walkingWeight = 0;
            dijkstra(map,parkingNode, destination, parsedArgs["AvoidNodes"], avoidSegments,walkingWeight,walkingDist,false);
            if (walkingDist[destination] == numeric_limits<double>::max()) continue;
            possibleParkingNodes.push_back(parkingNode);
            double totalTime = walkingWeight + dist[parkingNode];
            if (totalTime < bestTotalTime) {
                bestTotalTime = totalTime;
                bestParkingNode = parkingNode;
            }
        }
        if (!bestParkingNode) {
            cout << "Source:" << parsedArgs["Source"][0] << endl;
            cout << "Destination:" << parsedArgs["Destination"][0] << endl;
            cout << "DrivingRoute:" << endl;
            cout << "ParkingNode:" << endl;
            cout << "WalkingRoute:" << endl;
            cout << "TotalTime:" << endl;
            cout << "Message:No feasible environmentally-friendly route found within constraints. couldn't find suitable parking node." << endl;
            return;
        }

        //actual path
        double weight1 = 0;
        double weight2 = 0;
        unordered_map<City*,double> dist1;
        unordered_map<City*,double> dist2;
        vector<City *> path1 = dijkstra(map,source, bestParkingNode, parsedArgs["AvoidNodes"], avoidSegments,weight1,dist1);
        vector<City *> path2 = dijkstra(map,bestParkingNode, destination, parsedArgs["AvoidNodes"], avoidSegments,weight2,dist2,false);

        if (weight2> parsedArgs["MaxWalkTime"][0]) {
            cout << "Source:" << parsedArgs["Source"][0] << endl;
            cout << "Destination:" << parsedArgs["Destination"][0] << endl;
            cout << "DrivingRoute:none" << endl;
            cout << "ParkingNode:none" << endl;
            cout << "WalkingRoute:none" << endl;
            cout << "TotalTime:" << endl;
            cout << "Message:No feasible environmentally-friendly route found within constraints. walking time of " << parsedArgs["MaxWalkTime"][0] << " minutes." << endl;
            int index = 0;
            vector<pair<pair<vector<City *>,vector<City *>>,pair<double,double>>> suggestions;
            if (!possibleParkingNodes.empty()){
                for (auto p: possibleParkingNodes) {
                    double weight1p = 0;
                    double weight2p = 0;
                    unordered_map<City*,double> dist1p;
                    unordered_map<City*,double> dist2p;
                    vector<City *> path1p = dijkstra(map,source, p, parsedArgs["AvoidNodes"], avoidSegments,weight1p,dist1p);
                    vector<int> avoiding;
                    for (auto i:parsedArgs["AvoidNodes"]) {
                        avoiding.push_back(i);
                    }
                    auto iter = path1p.begin();
                    for (auto i:path1p) {
                        ++iter;
                        if (iter != path1p.end()) {
                            avoiding.push_back(i->getInfo().id);
                        }
                    }
                    vector<City *> path2p = dijkstra(map,p, destination, avoiding, avoidSegments,weight2p,dist2p,false);
                    pair<vector<City *>,vector<City *>> fullPath = make_pair(path1p,path2p);
                    pair<double,double> weights = make_pair(weight1p,weight2p);
                    pair<pair<vector<City *>,vector<City *>>,pair<double,double>> pair = make_pair(fullPath,weights);
                    suggestions.push_back(pair);
                }
            }
            if (!suggestions.empty()) {
                sort(suggestions.begin(),suggestions.end(),[](pair<pair<vector<City *>,vector<City *>>,pair<double,double>> &a, pair<pair<vector<City *>,vector<City *>>,pair<double,double>> &b) {
                    return (a.second.first + a.second.second) < (b.second.first + b.second.second);
                });
                cout << endl;
                cout << "===== SUGGESTIONS =====" << endl;
            }
            for (const auto& sugg:suggestions) {
                index++;
                if (index > 2) {
                    break;
                }
                vector<City*> path1p = sugg.first.first;
                vector<City*> path2p = sugg.first.second;
                double weight1p = sugg.second.first;
                double weight2p = sugg.second.second;
                if (!(path1p.empty() || path2p.empty())) {

                    cout << "Source:" << parsedArgs["Source"][0] << endl;
                    cout << "Destination:" << parsedArgs["Destination"][0] << endl;
                    cout << "DrivingRoute"<< index<<":";
                    auto iter = path1p.begin();
                    for (auto c: path1p) {
                        ++iter;
                        cout << c->getInfo().id;
                        if (iter != path1p.end()) cout << ",";
                    }
                    cout << "(" << weight1p << ")" << endl;
                    cout << "ParkingNode"<< index<<":" << path1p[path1p.size()-1]->getInfo().id << endl;
                    cout << "WalkingRoute"<< index<<":";
                    iter = path2p.begin();
                    for (auto c: path2p) {
                        ++iter;
                        cout << c->getInfo().id;
                        if (iter != path2p.end()) cout << ",";
                    }
                    cout << "(" << weight2p << ")" << endl;
                    cout << "TotalTime"<< index<<":" << weight1p + weight2p << endl;
                    cout << endl;
                }
            }

            return;
        }
        if (path1.empty() || path2.empty()) {
            cout << "Source:" << parsedArgs["Source"][0] << endl;
            cout << "Destination:" << parsedArgs["Destination"][0] << endl;
            cout << "DrivingRoute:" << endl;
            cout << "ParkingNode:" << endl;
            cout << "WalkingRoute:" << endl;
            cout << "TotalTime:" << endl;
            cout << "Message:No feasible environmentally-friendly route found within constraints. couldn't find paths." << endl;
            return;
        }
        cout << "Source:" << parsedArgs["Source"][0] << endl;
        cout << "Destination:" << parsedArgs["Destination"][0] << endl;
        cout << "DrivingRoute:";
        auto iter = path1.begin();
        for (auto c: path1) {
            ++iter;
            cout << c->getInfo().id;
            if (iter != path1.end()) cout << ",";
        }
        cout << "(" << weight1 << ")" << endl;
        cout << "ParkingNode:" << bestParkingNode->getInfo().id << endl;
        cout << "WalkingRoute:";
        iter = path2.begin();
        for (auto c: path2) {
            ++iter;
            cout << c->getInfo().id;
            if (iter != path2.end()) cout << ",";
        }
        cout << "(" << weight2 << ")" << endl;
        cout << "TotalTime:" << weight1 + weight2 << endl;
    } catch (...) {
        cout << "Couldn't get MapFactory from context." << endl;
    }
}
