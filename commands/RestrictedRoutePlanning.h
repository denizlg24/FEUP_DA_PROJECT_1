//
// Created by deniz on 3/19/2025.
//

#ifndef RESTRICTEDROUTEPLANNING_H
#define RESTRICTEDROUTEPLANNING_H
#include "Command.h"


class RestrictedRoutePlanning : public Command{
    void execute(Context *context, std::vector<std::string> args) override;
};



#endif //RESTRICTEDROUTEPLANNING_H
