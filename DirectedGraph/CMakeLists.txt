cmake_minimum_required(VERSION 3.5)
project(DirectedGraph)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Werror")
set(SOURCE_FILES AdjacencyMatrix.h AdjacencyList.h OrthogonalList.h test3.c)
add_executable(DirectedGraph ${SOURCE_FILES})