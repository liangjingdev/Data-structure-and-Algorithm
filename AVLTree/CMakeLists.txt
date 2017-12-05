cmake_minimum_required(VERSION 3.5)
project(AVLTree)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Werror")

set(SOURCE_FILES test.c core.h)
add_executable(AVLTree ${SOURCE_FILES})