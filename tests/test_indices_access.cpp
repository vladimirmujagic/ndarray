#include "catch.hpp"

#include "../src/ndarray.hpp"
#include "data.hpp"

using namespace std;


/**********************************************************************************************
*                  Indices access (i, j, k, ...) test scenarios                               *
**********************************************************************************************/
SCENARIO( "ndarray indices access", "[ndarray]" ) {
    GIVEN("index (i)") {
        ndarray<float> a1d(test_data->a1d_data, test_data->a1d_shape);

        WHEN("element is accessed") {
            float val = a1d(2);
            THEN("correct value is returned") {
                REQUIRE(val == 2);
            }
        }
    }

    GIVEN("indices (i, j)") {
        ndarray<float> a2d(test_data->a2d_data, test_data->a2d_shape);

        WHEN("element is accessed") {
            float val = a2d(3, 3);
            THEN("correct value is returned") {
                REQUIRE(val == 15);
            }
        }
    }

    GIVEN("indices (i, j, k)") {
        ndarray<float> a3d(test_data->a3d_data, test_data->a3d_shape);

        WHEN("element is accessed") {
            float val = a3d(1, 1, 1);
            THEN("correct value is returned") {
                REQUIRE(val == 16);
            }
        }
    }

    GIVEN("indices (i, j, k, l)") {
        ndarray<float> a4d(test_data->a4d_data, test_data->a4d_shape);

        WHEN("element is accessed") {
            float val = a4d(1, 1, 1, 2);
            THEN("correct value is returned") {
                REQUIRE(val == 47);
            }
        }
    }

    // ...
}
/**********************************************************************************************/