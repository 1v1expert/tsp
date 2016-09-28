cmake_minimum_required(VERSION 3.0)

project(tsp)

set(SOURCES src/main.cpp)
add_executable(tsp ${SOURCES})
set_property(TARGET tsp PROPERTY CXX_STANDARD 14)

