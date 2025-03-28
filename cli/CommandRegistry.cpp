//
// Created by deniz on 3/18/2025.
//

#include "CommandRegistry.h"

void CommandRegistry::registerDependency(const string &dependent, const string &dependency) {
    dependencies[dependent].push_back(dependency);
}

void CommandRegistry::registerCommand(const string& name, Command* command) {
    commands_map[name] = static_cast<int>(commandVector.size());
    commandVector.push_back(command);
    commandState[name] = false;
}

unordered_map<string,int> CommandRegistry::getCommands() {
    return commands_map;
}

Command* CommandRegistry::getCommand(int i) {
    return commandVector[i];
}


void CommandRegistry::executeCommand(const string &name, const vector<string> &args) {
    if (dependencies.find(name) != dependencies.end()) {
        for (const auto& dep : dependencies[name]) {
            if (!commandState[dep]) {
                cout << "Error: '" << name << "' requires '" << dep << "' to be executed first." << endl;
                return;
            }
        }
    }

    const auto it = commands_map.find(name);
    if (it != commands_map.end()) {
        try {
            commandVector[it->second]->execute(&context,args);
            commandState[name] = true;
        } catch (const exception& e) {
            cout << "Execution error: " << e.what() << endl;
        }
    } else {
        commandVector[commands_map["help"]]->execute(&context,{});
    }
}

Context * CommandRegistry::getContext() {
    return &context;
}

