cmake_minimum_required(VERSION 3.10)
project(csv_printer C)

set(CMAKE_C_STANDARD 99)

include_directories(include)

add_executable(csv_printer
    src/main.c
    src/csvParser.c
    src/tablePrinter.c
)

add_executable(tests
    tests/testCsv.c
    src/csvParser.c
    src/tablePrinter.c
)

enable_testing()
add_test(NAME tests COMMAND tests)
