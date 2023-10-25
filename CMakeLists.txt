cmake_minimum_required(VERSION 3.26)
project(Geom_Curves)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fopenmp")


add_executable(WorknotWolf testing_geoms.cpp curves.cpp curves.h)
