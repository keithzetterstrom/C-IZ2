cmake_minimum_required(VERSION 3.15)
project(multi_search C)

set(CMAKE_C_STANDARD 11)

add_library(multi_search src/multi_search.c include/multi_search.h)