//
// Created by Alex on 18/03/2025.
//

#include "PlanRoute.h"
#include "../utils/dijkstra.h"
#include "../utils/parseUtils.h"

#include <algorithm>
#include <unordered_set>

void PlanRoute::execute(Context *context, std::vector<std::string> args) {
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
    try {
        auto* factory = context->get<MapFactory>("map_factory");
        auto* map = factory->getMap();
        City *source = map->getCityById(parsedArgs["Source"][0]);
        City *destination = map->getCityById(parsedArgs["Destination"][0]);
        if (!source || !destination) {
            cout << "Source:" << parsedArgs["Source"][0] << endl;
            cout << "Destination:" << parsedArgs["Destination"][0] << endl;
            cout << "BestDrivingRoute:None" << endl;
            cout << "AlternativeDrivingRoute:None" << endl;
            return;
        };
        double weight1 = 0;
        vector<int> avoidNodes = {};
        vector<pair<int,int>> avoidSegments = {};
        unordered_map<City*,double> dist;
        vector<City *> result1 =  dijkstra(map,source, destination, avoidNodes, avoidSegments, weight1,dist);
        if (result1.empty()) {
            cout << "Source:" << parsedArgs["Source"][0] << endl;
            cout << "Destination:" << parsedArgs["Destination"][0] << endl;
            cout << "BestDrivingRoute:None" << endl;
            cout << "AlternativeDrivingRoute:None" << endl;
            return;
        }
        cout << "Source:" << parsedArgs["Source"][0] << endl;
        cout << "Destination:" << parsedArgs["Destination"][0] << endl;
        cout << "BestDrivingRoute:";
        auto iter = result1.begin();
        for (auto c: result1) {
            ++iter;
            cout << c->getInfo().id;
            if (iter != result1.end()) {
                cout << ",";
                if (iter != result1.begin()+1) {
                    avoidNodes.push_back(c->getInfo().id);
                }
            }
        }
        cout << "(" << weight1 << ")" << endl;
        double weight2 = 0;
        unordered_map<City*,double> dist2;
        vector<City *> result2 =  dijkstra(map,source, destination, avoidNodes, avoidSegments,weight2,dist2);
        if(result2.empty()) {
            cout << "AlternativeDrivingRoute:None" << endl;
            return;
        }
        cout << "AlternativeDrivingRoute:";
        iter = result2.begin();
        for(auto c: result2) {
            ++iter;
            cout << c->getInfo().id;
            if (iter != result2.end()) cout << ",";
        }
        cout << "(" << weight2 << ")" << endl;
    } catch (...) {
        cout << "Couldn't get MapFactory from context." << endl;
    }
}
