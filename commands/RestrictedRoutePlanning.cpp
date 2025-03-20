//
// Created by deniz on 3/19/2025.
//

#include "RestrictedRoutePlanning.h"
#include "../utils/dijkstra.h"
#include "../utils/parseUtils.h"

#include <algorithm>
#include <unordered_set>

void RestrictedRoutePlanning::execute(Context *context, std::vector<std::string> args) {
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
    if (parsedArgs.find("IncludeNode") == parsedArgs.end()) {
        cout << "IncludeNode argument not provided." << endl;
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
        if (parsedArgs["IncludeNode"].empty()) {
            double weight = 0;
            unordered_map<City*,double> dist;
            vector<City *> result =  dijkstra(map,source, destination, parsedArgs["AvoidNodes"], avoidSegments,weight,dist);
            if (result.empty()) {
                cout << "Source:" << parsedArgs["Source"][0] << endl;
                cout << "Destination:" << parsedArgs["Destination"][0] << endl;
                cout << "RestrictedDrivingRoute:None" << endl;
                return;
            }
            cout << "Source:" << parsedArgs["Source"][0] << endl;
            cout << "Destination:" << parsedArgs["Destination"][0] << endl;
            cout << "RestrictedDrivingRoute:";
            auto iter = result.begin();
            for (auto c: result) {
                ++iter;
                cout << c->getInfo().id;
                if (iter != result.end()) cout << ",";

            }
            cout << "(" << weight << ")" << endl;
        } else {
            City *includeCity = map->getCityById(parsedArgs["IncludeNode"][0]);
            if (!includeCity) {
                cout << "Source:" << parsedArgs["Source"][0] << endl;
                cout << "Destination:" << parsedArgs["Destination"][0] << endl;
                cout << "RestrictedDrivingRoute:None" << endl;
                return;
            };
            double weight1 = 0;
            double weight2 = 0;
            unordered_map<City*,double> dist1;
            unordered_map<City*,double> dist2;
            vector<City *> path1 = dijkstra(map,source, includeCity, parsedArgs["AvoidNodes"], avoidSegments,weight1,dist1);
            vector<City *> path2 = dijkstra(map,includeCity, destination, parsedArgs["AvoidNodes"], avoidSegments,weight2,dist2);

            if (path1.empty() || path2.empty()) {
                cout << "Source:" << parsedArgs["Source"][0] << endl;
                cout << "Destination:" << parsedArgs["Destination"][0] << endl;
                cout << "RestrictedDrivingRoute:None" << endl;
                return;
            };

            path1.pop_back();
            path1.insert(path1.end(), path2.begin(), path2.end());
            cout << "Source:" << parsedArgs["Source"][0] << endl;
            cout << "Destination:" << parsedArgs["Destination"][0] << endl;
            cout << "RestrictedDrivingRoute:";
            auto iter = path1.begin();
            for (auto c: path1) {
                ++iter;
                cout << c->getInfo().id;
                if (iter != path1.end()) cout << ",";
            }
            cout << "(" << weight1 + weight2 << ")" << endl;
        }
    } catch (...) {
        cout << "Couldn't get MapFactory from context." << endl;
    }
}
