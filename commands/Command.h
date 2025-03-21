//
// Created by deniz on 3/18/2025.
//

#ifndef COMMAND_H
#define COMMAND_H
#include "../context/Context.h"
#include <string>
#include <vector>
#include "../data_structures/MapFactory.h"

/// @class Command
/// @brief Abstract base class for defining commands that can be executed within a context.
class Command {
public:
    /// @brief Executes the command with the given context and arguments.
    /// @param context Pointer to the execution context.
    /// @param args List of arguments for the command.
    virtual void execute(Context* context, std::vector<std::string> args);
};
#endif //COMMAND_H
