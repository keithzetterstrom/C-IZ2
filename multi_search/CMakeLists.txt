cmake_minimum_required(VERSION 3.15)
project(multi_search C)

set(CMAKE_C_STANDARD 11)

add_library(multi_search src/multi_search.c include/multi_search.h)

if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
target_compile_definitions(multi_search PUBLIC "IS_MACOS")
endif()
if (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
target_compile_definitions(multi_search PUBLIC "IS_LINUX")
endif()