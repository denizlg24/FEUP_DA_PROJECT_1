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


    streambuf* cinBackup = cin.rdbuf();
    streambuf* coutBackup = cout.rdbuf();
    ifstream inputFile;
    ofstream outputFile;
    bool inputFlag = false;

    vector<string> fArgs = args;

    for (size_t i = 0; i < fArgs.size(); ++i) {
        if (fArgs[i] == "<" && i + 1 < fArgs.size()) {
            inputFile.open(fArgs[i + 1]);
            if (!inputFile) {
                cout << "Error: Cannot open input file " << fArgs[i + 1] << endl;
                return;
            }
            cin.rdbuf(inputFile.rdbuf());
            fArgs.erase(fArgs.begin() + i, fArgs.begin() + i + 2);
            i--;
            inputFlag = true;
        } else if (fArgs[i] == ">" && i + 1 < fArgs.size()) {
            outputFile.open(fArgs[i + 1]);
            if (!outputFile) {
                cout << "Error: Cannot open output file " << fArgs[i + 1] << endl;
                return;
            }
            cout.rdbuf(outputFile.rdbuf());
            fArgs.erase(fArgs.begin() + i, fArgs.begin() + i + 2);
            i--;
        }
    }

    if (inputFlag) {
        string line;
        while (getline(cin, line)) {
            fArgs.push_back(line);
        }
    }

    if (inputFile.is_open()) {
        inputFile.close();
    }
    cin.rdbuf(cinBackup);

    const auto it = commands_map.find(name);
    if (it != commands_map.end()) {
        try {
            commandVector[it->second]->execute(&context,fArgs);
            commandState[name] = true;
        } catch (const exception& e) {
            cout << "Execution error: " << e.what() << endl;
        }
    } else {
        commandVector[commands_map["help"]]->execute(&context,{});
    }

    cout.rdbuf(coutBackup);
    if (outputFile.is_open()) {
        outputFile.close();
    }

}

Context * CommandRegistry::getContext() {
    return &context;
}

