//
// Created by Alex on 18/03/2025.
//

#include "PlanRoute.h"

void PlanRoute::execute(Context *context, std::vector<std::string> args) {
    if (args.size() != 4) { // 4 for now as the remaining options aren't implemented
        cout << "Correct usage --> plan_route Mode:<mode> Source:<id> Destination:<id>" << endl;
    }
}
