cmake_minimum_required(VERSION 3.1)
project(CommandTerminal)

#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pedantic -Wall -O4")

set(SOURCE_FILES main.c)
add_executable(CommandTerminal ${SOURCE_FILES} check_env.h check_env.c routing.h routing.c main.h system_navigation.h system_navigation.c new_processes.h new_processes.c signal_handler.h signal_handler.c)