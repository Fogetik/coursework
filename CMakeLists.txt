cmake_minimum_required(VERSION 3.21)
project(kursah)

set(CMAKE_CXX_STANDARD 23)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

add_executable(kursah main.cpp node.h rbTree.cpp rbTree.h comparator.h)
