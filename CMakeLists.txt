cmake_minimum_required(VERSION 3.14)
project(transitRoutePlanner LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(transitRoutePlanner
    src/main.cpp
    src/application.cpp
    src/output.cpp
    src/parser.cpp
    src/stationIndex.cpp
    src/stringUtils.cpp
    src/transportNetwork.cpp
)

target_include_directories(transitRoutePlanner PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

enable_testing()

add_executable(networkTest tests/networkTest.cpp
    src/stationIndex.cpp
    src/stringUtils.cpp
    src/transportNetwork.cpp
    src/parser.cpp
    src/output.cpp
)
target_include_directories(networkTest PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
add_test(NAME networkTest COMMAND networkTest)

add_executable(parserTest tests/parserTest.cpp
    src/stationIndex.cpp
    src/stringUtils.cpp
    src/parser.cpp
    src/transportNetwork.cpp
    src/output.cpp
)
target_include_directories(parserTest PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
add_test(NAME parserTest COMMAND parserTest)
