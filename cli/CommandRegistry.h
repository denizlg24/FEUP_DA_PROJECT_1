//
// Created by deniz on 3/18/2025.
//

#ifndef COMMANDREGISTRY_H
#define COMMANDREGISTRY_H
#include "../commands/Command.h"
using namespace std;

class CommandRegistry {
public:
    void registerCommand(const string &name, Command* command);
    unordered_map<string,int> getCommands();
    Command* getCommand(int i);
    void registerDependency(const string &dependent, const string &dependency);
    void executeCommand(const string& name, const vector<string>& args);
    Context * getContext();
protected:
    vector<Command*> commandVector;
    unordered_map<string, int> commands_map;
    unordered_map<string, bool> commandState;
    unordered_map<string,vector<string>> dependencies;
    Context context;
};



#endif //COMMANDREGISTRY_H
