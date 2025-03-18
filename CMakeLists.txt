cmake_minimum_required(VERSION 3.26)
project(FEUP_DA_PROJECT_1)

set(CMAKE_CXX_STANDARD 14)
set( CMAKE_BUILD_TYPE_TMP "${CMAKE_BUILD_TYPE}" )
set( CMAKE_BUILD_TYPE "Release" )

include_directories(data input data_structures csv_parser)
add_executable(FEUP_DA_PROJECT_1
        main.cpp
        csv_parser/CSVParser.cpp
        cli/CommandRegistry.cpp
        cli/CommandRegistry.h
        commands/Command.h
        cli/CLI.cpp
        cli/CLI.h
        commands/HelpCommand.h
        context/Context.h
        commands/ReadCities.h
        commands/ReadRoads.h
        commands/ReadCities.cpp
        commands/ReadRoads.cpp
        commands/Help.cpp
        commands/Command.cpp
)

set( CMAKE_BUILD_TYPE ${CMAKE_BUILD_TYPE_TMP} )

#add_definitions(-D_ITERATOR_DEBUG_LEVEL=0)
#set(CMAKE_CXX_FLAGS_DEBUG "/MDd")  # Para Debug
#set(CMAKE_CXX_FLAGS_RELEASE "/MD") # Para Release
target_link_libraries(FEUP_DA_PROJECT_1)
add_custom_target(copy_data ALL
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/data ${CMAKE_BINARY_DIR}/data
)

add_dependencies(FEUP_DA_PROJECT_1 copy_data)