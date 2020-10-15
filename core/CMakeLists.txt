cmake_minimum_required(VERSION 3.10)

project(libndarray)

set(SOURCES
    src/ndarray.cpp
    src/ndarray_utils.cpp
    src/ndarray_validation.cpp
)

add_library(ndarray SHARED ${SOURCES})
add_library(ndarray::library ALIAS ndarray)
target_include_directories(ndarray INTERFACE ./include)