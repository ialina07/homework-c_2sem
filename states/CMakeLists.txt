cmake_minimum_required(VERSION 3.10)
project(cityDistributor C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

option(BUILD_TESTS "Build tests" ON)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

set(SOURCES
    src/graph.c
    src/state.c
    src/distributor.c
)

add_executable(cityDistributor src/main.c ${SOURCES})

if(BUILD_TESTS)
    enable_testing()
    
    add_executable(graphTests tests/testGraph.c ${SOURCES})
    add_executable(stateTests tests/testState.c ${SOURCES})
    add_executable(distributorTests tests/testDistributor.c ${SOURCES})
    
    add_test(NAME graphTests COMMAND graphTests)
    add_test(NAME stateTests COMMAND stateTests)
    add_test(NAME distributorTests COMMAND distributorTests)
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_options(-g -O0 -Wall -Wextra)
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    add_compile_options(-O3 -DNDEBUG)
endif()