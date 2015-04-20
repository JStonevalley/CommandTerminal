cmake_minimum_required(VERSION 3.1)
project(CommandTerminal)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pedantic -Wall -ansi -O4")

set(SOURCE_FILES main.c)
add_executable(CommandTerminal ${SOURCE_FILES} structs.h routing.h routing.c main.h system_navigation.h system_navigation.c)