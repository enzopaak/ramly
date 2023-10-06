cmake_minimum_required(VERSION 3.26)
project(testing)

set(CMAKE_CXX_STANDARD 23)

add_executable(testing main.cpp bmplib.cpp bmplib.h)
