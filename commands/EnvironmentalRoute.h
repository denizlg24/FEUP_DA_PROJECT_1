//
// Created by deniz on 3/20/2025.
//

#ifndef ENVIRONMENTALROUTE_H
#define ENVIRONMENTALROUTE_H
#include "Command.h"


class EnvironmentalRoute : public  Command {
    void execute(Context *context, std::vector<std::string> args) override;
};



#endif //ENVIRONMENTALROUTE_H
