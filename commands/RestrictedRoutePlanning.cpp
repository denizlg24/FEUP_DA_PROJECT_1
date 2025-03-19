//
// Created by deniz on 3/19/2025.
//

#include "RestrictedRoutePlanning.h"

#include <algorithm>
#include <limits>
#include <queue>
#include <sstream>
#include <unordered_set>

vector<int> parseCommaSeparated(const string &input) {
    vector<int> result;
    stringstream ss(input);
    string num;

    while (getline(ss, num, ',')) {
        if (!num.empty()) result.push_back(stoi(num));
    }
    return result;
}

vector<int> parseSegments(const string &input) {
    vector<int> result;
    stringstream ss(input);
    string segment;

    while (getline(ss, segment, ')')) {
        if (segment.empty()) continue;
        size_t start = segment.find('(');
        if (start != string::npos) {
            segment = segment.substr(start + 1);
        }

        stringstream segStream(segment);
        string num;
        while (getline(segStream, num, ',')) {
            if (!num.empty()) result.push_back(stoi(num));
        }
    }
    return result;
}

unordered_map<string, vector<int>> parseInput(const vector<string> &inputLines) {
    unordered_map<string, vector<int>> parsedData;

    for (const string &line : inputLines) {
        size_t colonPos = line.find(':');
        if (colonPos == string::npos) continue;

        string key = line.substr(0, colonPos);
        string value = line.substr(colonPos + 1);

        key.erase(remove_if(key.begin(), key.end(), ::isspace), key.end());
        value.erase(remove_if(value.begin(), value.end(), ::isspace), value.end());



        if (key == "Mode") {
            if (value.empty()) {
                parsedData[key] = {};
                continue;
            }
            parsedData[key] = {value == "driving" ? 0 : 1};
        }
        else if (key == "Source" || key == "Destination" || key == "IncludeNode") {
            if (value.empty()) {
                parsedData[key] = {};
                continue;
            }
            parsedData[key] = {stoi(value)};
        }
        else if (key == "AvoidNodes") {
            if (value.empty()) {
                parsedData[key] = {};
                continue;
            }
            parsedData[key] = parseCommaSeparated(value);
        }
        else if (key == "AvoidSegments") {
            if (value.empty()) {
                parsedData[key] = {};
                continue;
            }
            parsedData[key] = parseSegments(value);
        }
    }

    return parsedData;
}

vector<City *> dijkstra(const Map* map,City *start, City *end,
                                      const vector<int> &avoidNodes,
                                      const vector<pair<int, int>> &avoidSegments,double& weight) {
    unordered_map<City *, double> dist;
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
            if (!road->isDrivable())continue;
            double weight = road->getDrivingWeight();
            if (dist[current] + weight < dist[neighbor]) {
                dist[neighbor] = dist[current] + weight;
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
            vector<City *> result =  dijkstra(map,source, destination, parsedArgs["AvoidNodes"], avoidSegments,weight);
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
            vector<City *> path1 = dijkstra(map,source, includeCity, parsedArgs["AvoidNodes"], avoidSegments,weight1);
            vector<City *> path2 = dijkstra(map,includeCity, destination, parsedArgs["AvoidNodes"], avoidSegments,weight2);

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
