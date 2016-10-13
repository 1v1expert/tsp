cmake_minimum_required(VERSION 3.0)

project(tsp)

set(SOURCES src/main.cpp)
add_executable(tsp ${SOURCES})

if(CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "-O3")
endif()

set_property(TARGET tsp PROPERTY CXX_STANDARD 14)

