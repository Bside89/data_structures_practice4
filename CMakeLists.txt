cmake_minimum_required(VERSION 3.5)
project(TP4)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c99")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")

set(SOURCE_FILES main.c tadbasics/xcpt.h tadbasics/xcpt.c
                        tadbasics/graph.h tadbasics/graph.c
                        tadbasics/cell.h tadbasics/cell.c
                        tadbasics/stack.h tadbasics/stack.c)

add_executable(TP4 ${SOURCE_FILES})