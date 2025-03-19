//
// Created by Alex on 18/03/2025.
//

#ifndef PLANROUTE_H
#define PLANROUTE_H

#include "Command.h"

class PlanRoute : public Command{
    void execute(Context *context, std::vector<std::string> args) override;
};

#endif //PLANROUTE_H
