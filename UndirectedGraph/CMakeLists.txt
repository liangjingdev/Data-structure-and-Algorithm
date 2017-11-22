cmake_minimum_required(VERSION 3.5)
project(UndirectedGraph)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Werror")

set(SOURCE_FILES  test1.c AdjacencyMatrix.h AdjacencyList.h)
add_executable(UndirectedGraph ${SOURCE_FILES})