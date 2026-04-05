cmake_minimum_required(VERSION 3.10)
project(dfa_number_checker C)

set(CMAKE_C_STANDARD 99)

include_directories(include)

add_executable(number_checker
    src/main.c
    src/dfa.c
)

add_executable(tests
    tests/testDfa.c
    src/dfa.c
)

enable_testing()
add_test(NAME tests COMMAND tests)
