//
// Created by deniz on 3/18/2025.
//

#ifndef READCITIES_H
#define READCITIES_H


#include "Command.h"


class ReadCities : public Command{
    void execute(Context *context, std::vector<std::string> args) override;
};




#endif //READCITIES_H
