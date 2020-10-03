cmake_minimum_required(VERSION 3.10)

project(catch2)

add_library(catch2 INTERFACE)
add_library(catch2::library ALIAS catch2)
target_include_directories(catch2 INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})