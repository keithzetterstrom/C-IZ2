cmake_minimum_required(VERSION 3.15)
project(single_search C)

set(CMAKE_C_STANDARD 11)

add_library(single_search SHARED src/single_search.c include/single_search.h)