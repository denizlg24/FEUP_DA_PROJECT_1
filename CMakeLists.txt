cmake_minimum_required(VERSION 3.26)
project(FEUP_DA_PROJECT_1)

set(CMAKE_CXX_STANDARD 14)
set( CMAKE_BUILD_TYPE_TMP "${CMAKE_BUILD_TYPE}" )
set( CMAKE_BUILD_TYPE "Release" )
add_executable(main.cpp
        data_structures/Map.h
        data_structures/MapFactory.h)