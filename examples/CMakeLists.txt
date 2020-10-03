cmake_minimum_required(VERSION 3.10)

project(ndarray_examples)
if(NOT TARGET ndarray)
    add_subdirectory(../core ndarray)
endif()

##########################################################
#        1. Test constructor                             #
##########################################################
add_executable(reshape_example src/reshape.cpp)
target_link_libraries(reshape_example ndarray::library)
##########################################################