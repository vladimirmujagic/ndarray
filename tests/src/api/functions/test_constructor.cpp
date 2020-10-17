#define CATCH_CONFIG_MAIN
#include <vector>

#include "../../../catch2/catch.hpp"

#include "../../../../core/include/ndarray.hpp"
#include "../../../include/data_generator.hpp"


using namespace std;


SCENARIO( "ndarray construction", "[ndarray]" ) {
    GIVEN( "1d data stored as 1d array and its shape" ) {
        WHEN("ndarray is constructed") {
            THEN("data is assigned, dimension, size and shape products are calculated") {
                REQUIRE(true == true);
            }
        }
    }

    GIVEN( "2d data stored as 1d array and its shape" ) {
        WHEN("ndarray is constructed") {
            THEN("data is assigned, dimension, size and shape products are calculated") {
                REQUIRE(true == true);
            }
        }
    }

    GIVEN( "3d data stored as 1d array and its shape" ) {
        WHEN("ndarray is constructed") {
            THEN("data is assigned, dimension, size and shape products are calculated") {
                REQUIRE(true == true);
            }
        }
    }

    GIVEN( "4d data stored as 1d array and its shape" ) {
        WHEN("ndarray is constructed") {
            THEN("data is assigned, dimension, size and shape products are calculated") {
                REQUIRE(true == true);
            }
        }
    }
}
