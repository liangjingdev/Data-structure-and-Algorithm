cmake_minimum_required(VERSION 3.5)
project(Union_find_Sets)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Werror")

set(SOURCE_FILES test.c core.h)
add_executable(Union_find_Sets ${SOURCE_FILES})