//
// Created by deniz on 3/18/2025.
//

#ifndef COMMANDREGISTRY_H
#define COMMANDREGISTRY_H
#include "../commands/Command.h"
using namespace std;
/// @class CommandRegistry
/// @brief Manages the registration, execution, and dependencies of commands.
class CommandRegistry {
public:
    /// @brief Registers a command with a given name.
    /// @param name The name of the command.
    /// @param command Pointer to the Command object.
    void registerCommand(const string &name, Command* command);

    /// @brief Retrieves the map of registered commands.
    /// @return An unordered map of command names to their respective indices.
    unordered_map<string,int> getCommands();
    /// @brief Retrieves a command by its index.
    /// @param i The index of the command.
    /// @return Pointer to the Command object.
    Command* getCommand(int i);
    /// @brief Registers a dependency between commands.
    /// @param dependent The name of the dependent command.
    /// @param dependency The name of the command it depends on.
    void registerDependency(const string &dependent, const string &dependency);

    /// @brief Executes a command by name with the given arguments.
    /// @param name The name of the command to execute.
    /// @param args The list of arguments for the command.
    void executeCommand(const string& name, const vector<string>& args);
    /// @brief Retrieves the command execution context.
    /// @return Pointer to the Context object.
    Context * getContext();
protected:
    vector<Command*> commandVector;
    unordered_map<string, int> commands_map;
    unordered_map<string, bool> commandState;
    unordered_map<string,vector<string>> dependencies;
    Context context;
};



#endif //COMMANDREGISTRY_H
