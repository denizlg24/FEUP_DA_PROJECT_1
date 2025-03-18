//
// Created by deniz on 3/18/2025.
//

#ifndef COMMAND_H
#define COMMAND_H
#include "../context/Context.h"
#include <string>
#include <vector>
#include "../data_structures/MapFactory.h"


class Command {
public:
    virtual void execute(Context* context, std::vector<std::string> args);
};
#endif //COMMAND_H
