cmake_minimum_required(VERSION 3.5)
project(InfixEval)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")

set(SOURCE_FILES main.c stack.c stack.h)
add_executable(InfixEval ${SOURCE_FILES})