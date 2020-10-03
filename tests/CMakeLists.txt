cmake_minimum_required(VERSION 3.10)

project(ndarray_tests)
if(NOT TARGET catch2)
    add_subdirectory(catch2)
endif()
if(NOT TARGET ndarray)
    add_subdirectory(../core ndarray)
endif()

##########################################################
#        1. Test constructor                             #
##########################################################
add_executable(ndarray_test_constructor src/test_constructor.cpp)
target_link_libraries(ndarray_test_constructor
        ndarray::library
        catch2::library
)
target_include_directories(ndarray_test_constructor PRIVATE ./include)
##########################################################

###########################################################
##        2. Test view                                    #
###########################################################
add_executable(ndarray_test_view src/test_view.cpp)
target_link_libraries(ndarray_test_view
    ndarray::library
    catch2::library
)
target_include_directories(ndarray_test_view PRIVATE ./include)
###########################################################

###########################################################
##        3. Test copy                                    #
###########################################################
add_executable(ndarray_test_copy src/test_copy.cpp)
target_link_libraries(ndarray_test_copy
    ndarray::library
    catch2::library
)
target_include_directories(ndarray_test_copy PRIVATE ./include)
###########################################################

###########################################################
##        4. Test indices access                          #
###########################################################
add_executable(ndarray_test_indices_access src/test_indices_access.cpp)
target_link_libraries(ndarray_test_indices_access
    ndarray::library
    catch2::library
)
target_include_directories(ndarray_test_indices_access PRIVATE ./include)
###########################################################

###########################################################
##        5. Test operators                               #
###########################################################
add_executable(ndarray_test_operators src/test_operators.cpp)
target_link_libraries(ndarray_test_operators
    ndarray::library
    catch2::library
)
target_include_directories(ndarray_test_operators PRIVATE ./include)
###########################################################


enable_testing()
add_test(test_constructor     ndarray_test_constructor)
add_test(test_view            ndarray_test_view)
add_test(test_copy            ndarray_test_copy)
add_test(test_indices_access  ndarray_test_indices_access)
add_test(test_operators       ndarray_test_operators)