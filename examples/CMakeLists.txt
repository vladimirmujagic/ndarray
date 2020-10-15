cmake_minimum_required(VERSION 3.10)

project(ndarray_examples)
if(NOT TARGET ndarray)
    add_subdirectory(../core ndarray)
endif()


##########################################################################
#        1. at                                                           #
##########################################################################
add_executable(example_at src/example_at.cpp)
target_link_libraries(example_at ndarray::library)
##########################################################################

##########################################################################
#        2. constructor                                                  #
##########################################################################
add_executable(example_constructor src/example_constructor.cpp)
target_link_libraries(example_constructor ndarray::library)
#########################################################################

#########################################################################
#        3. copy_at                                                     #
#########################################################################
add_executable(example_copy_at src/example_copy_at.cpp)
target_link_libraries(example_copy_at ndarray::library)
#########################################################################

#########################################################################
#        4. indices_access                                              #
#########################################################################
add_executable(example_indices_access src/example_indices_access.cpp)
target_link_libraries(example_indices_access ndarray::library)
#########################################################################

#########################################################################
#        5. operators                                                   #
#########################################################################
add_executable(example_operators src/example_operators.cpp)
target_link_libraries(example_operators ndarray::library)
#########################################################################

#########################################################################
#        6. reshape                                                     #
#########################################################################
add_executable(example_reshape src/example_reshape.cpp)
target_link_libraries(example_reshape ndarray::library)
#########################################################################

#########################################################################
#        6. element wise                                                #
#########################################################################
add_executable(example_element_wise src/example_element_wise.cpp)
target_link_libraries(example_element_wise ndarray::library)
#########################################################################