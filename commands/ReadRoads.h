//
// Created by deniz on 3/18/2025.
//

#ifndef READROADS_H
#define READROADS_H
#include "Command.h"


class ReadRoads : public Command{
    void execute(Context *context, std::vector<std::string> args) override;
};

#endif //READROADS_H
