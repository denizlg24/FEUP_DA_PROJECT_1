//
// Created by deniz on 3/21/2025.
//

#ifndef READFROMFILE_H
#define READFROMFILE_H
#include "Command.h"


class ReadFromFile : public Command {
    void execute(Context *context, std::vector<std::string> args) override;
};



#endif //READFROMFILE_H
