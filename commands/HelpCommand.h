//
// Created by deniz on 3/18/2025.
//

#ifndef HELPCOMMAND_H
#define HELPCOMMAND_H
#include "Command.h"
using namespace std;

class HelpCommand : public Command{
    void execute(Context* context,std::vector<std::string> args) override;
};




#endif //HELPCOMMAND_H
