cmake_minimum_required(VERSION 3.10)
project(aerosoft C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra")

include_directories(src)

add_executable(aerosoft
    src/main.c
    src/avl.c
)