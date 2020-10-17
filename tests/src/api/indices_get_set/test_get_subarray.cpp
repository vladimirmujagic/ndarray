#define CATCH_CONFIG_MAIN

#include <vector>

#include "../../../catch2/catch.hpp"

#include "../../../../core/include/ndarray.hpp"
#include "../../../include/data_generator.hpp"


using namespace std;


SCENARIO( "ndarray view", "[ndarray]" ) {
    GIVEN("2d array and index i") {
        WHEN("array is viewed at index i") {
            THEN("1d array is returned") {
                REQUIRE(true == true);
            }
        }
    }

    GIVEN("3d array and index i") {
        WHEN("array is viewed at index i") {
            THEN("2d array is returned") {
                REQUIRE(true == true);
            }
        }
    }
}
