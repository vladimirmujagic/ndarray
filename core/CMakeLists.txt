cmake_minimum_required(VERSION 3.10)

project(libndarray)

# add_definitions(-DDEBUG=1)

set(CMAKE_CXX_FLAGS_RELEASE "-O3")

set(SOURCES
    src/ndarray.cpp
    src/ndarray_validation.cpp
    src/ndarray_utils.cpp
)

add_library(ndarray SHARED ${SOURCES})
add_library(ndarray::library ALIAS ndarray)
target_include_directories(ndarray INTERFACE ./include)