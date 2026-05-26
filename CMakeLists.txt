cmake_minimum_required(VERSION 3.10)
project(shortest_path)

set(CMAKE_CXX_STANDARD 17)

add_executable(shortest_path
        src/application.cpp
        src/main.cpp
        src/output.cpp
        src/parser.cpp
        src/stationIndex.cpp
        src/stringUtils.cpp
        src/transportNetwork.cpp)
target_include_directories(shortest_path PRIVATE include/transit)
