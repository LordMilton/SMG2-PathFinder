cmake_minimum_required(VERSION 3.13)
project(PathFinder VERSION 0.1)

add_library(PathFinder "")

add_subdirectory(src/)
add_subdirectory(inc/)

include_directories(inc/)