cmake_minimum_required(VERSION 3.5)
project(BinarySortTree)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Werror")

set(SOURCE_FILES test.c core.h)
add_executable(BinarySortTree ${SOURCE_FILES})
