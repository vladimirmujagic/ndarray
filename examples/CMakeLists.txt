cmake_minimum_required(VERSION 3.10)

project(ndarray_examples)
enable_testing()

if(NOT TARGET ndarray)
    add_subdirectory(../core ndarray)
endif()

file(GLOB_RECURSE files "src/*.cpp")
foreach(file_path ${files})
    get_filename_component(file_name ${file_path} NAME_WE)
    add_executable(${file_name} ${file_path})
    target_link_libraries(${file_name} ndarray::library)
endforeach()
