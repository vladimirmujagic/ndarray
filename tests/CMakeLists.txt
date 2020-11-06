cmake_minimum_required(VERSION 3.10)

project(ndarray_tests)
enable_testing()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT TARGET catch2)
    add_subdirectory(catch2)
endif()
if(NOT TARGET ndarray)
    add_subdirectory(../core ndarray)
endif()

file(GLOB_RECURSE files "src/*.cpp")
foreach(file_path ${files})
    get_filename_component(file_name ${file_path} NAME_WE)
    add_executable(${file_name} ${file_path})
    target_link_libraries(${file_name} ndarray::library catch2::library)

    add_test(${file_name} ${file_name})
endforeach()
