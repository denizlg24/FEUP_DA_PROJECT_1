//
// Created by deniz on 3/17/2025.
//
#include "data_structures/MapFactory.h"
#include <string>

#include "cli/CLI.h"
#include "cli/CommandRegistry.h"
#include "commands/HelpCommand.h"
#include "commands/ReadCities.h"
#include "commands/ReadRoads.h"
#include "commands/RestrictedRoutePlanning.h"


int main(int argc, char* argv[]) {
    auto *factory = new MapFactory();
    auto *registry = new CommandRegistry();
    registry->getContext()->set("map_factory",*factory);
    registry->registerCommand("read_cities",new ReadCities());
    registry->registerCommand("read_roads",new ReadRoads());
    registry->registerCommand("help",new HelpCommand());
    registry->registerCommand("commands",new HelpCommand());
    registry->registerCommand("restricted_route_planning",new RestrictedRoutePlanning());
    registry->registerDependency("read_roads", "read_cities");
    registry->registerDependency("restricted_route_planning","read_cities");
    registry->registerDependency("restricted_route_planning","read_roads");
    CLI::run(*registry);
    return 0;
}
