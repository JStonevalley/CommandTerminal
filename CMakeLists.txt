cmake_minimum_required(VERSION 3.1)
project(CommandTerminal)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror")

set(SOURCE_FILES main.c)
add_executable(CommandTerminal ${SOURCE_FILES})