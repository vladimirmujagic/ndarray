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
add_executable(ndarray_test_at src/test_at.cpp)
target_link_libraries(ndarray_test_at
    ndarray::library
    catch2::library
)
target_include_directories(ndarray_test_at PRIVATE ./include)
###########################################################

###########################################################
##        3. Test copy                                    #
###########################################################
add_executable(ndarray_test_copy_at src/test_copy_at.cpp)
target_link_libraries(ndarray_test_copy_at
    ndarray::library
    catch2::library
)
target_include_directories(ndarray_test_copy_at PRIVATE ./include)
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

###########################################################
##        6. Test reshape                                 #
###########################################################
add_executable(ndarray_test_reshape src/test_reshape.cpp)
target_link_libraries(ndarray_test_reshape
    ndarray::library
    catch2::library
)
target_include_directories(ndarray_test_reshape PRIVATE ./include)
###########################################################

enable_testing()
add_test(test_constructor     ndarray_test_constructor)
add_test(test_at              ndarray_test_at)
add_test(test_copy_at         ndarray_test_copy_at)
add_test(test_indices_access  ndarray_test_indices_access)
add_test(test_operators       ndarray_test_operators)
add_test(test_reshape         ndarray_test_reshape)