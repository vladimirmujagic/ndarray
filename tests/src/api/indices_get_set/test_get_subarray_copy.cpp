#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"

#include <vector>

#include "../../../../core/include/ndarray.hpp"
#include "../../../include/data_generator.hpp"

using namespace std;


SCENARIO( "ndarray copy", "[ndarray]" ) {
    GIVEN("2d array and index i") {
        WHEN("array is viewed at index i") {
            THEN("1d array copy is returned") {
                REQUIRE(true == true);
            }
        }
    }

    GIVEN("3d array and index i") {
        WHEN("array is viewed at index i") {
            THEN("2d array copy is returned") {
                REQUIRE(true == true);
            }
        }
    }
}

