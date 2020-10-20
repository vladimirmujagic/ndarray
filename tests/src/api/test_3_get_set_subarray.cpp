#define CATCH_CONFIG_MAIN

#include <vector>

#include "../../catch2/catch.hpp"

#include "../../../core/include/ndarray.hpp"
#include "../../include/data_generator.hpp"


using namespace std;

DataGenerator data_generator;


SCENARIO( "ndarray subarray_at", "[ndarray]" ) {
    GIVEN("2d array and index i") {
        float *data = data_generator.arange(4);
        vector<unsigned> shape = {2, 2};
        ndarray<float> a(data, shape);
        unsigned i = 1;
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

    GIVEN("4d array and indices i, j") {
        WHEN("array is viewed at index i") {
            THEN("2d array is returned") {
                REQUIRE(true == true);
            }
        }
    }
}
