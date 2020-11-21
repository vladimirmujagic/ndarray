#define CATCH_CONFIG_MAIN
#include <vector>

#include "../../catch2/catch.hpp"

#include "../../../core/include/ndarray.hpp"
#include "../../include/data_generator.hpp"


using namespace std;

DataGenerator<float> data_generator;


SCENARIO( "ndarray reshape", "[ndarray]" ) {
    GIVEN("3d array with shape (5, 2, 2)") {
        ndarray<float> a(1., {5, 2, 2});
        WHEN("array is reshaped to (2, 2, 5)") {
            a.reshape({2, 2, 5});
            THEN("proper dimension new shape and strides are assigned") {
                REQUIRE(a.dim == 3);
                REQUIRE(a.shape == vector<unsigned>{2, 2, 5});
                REQUIRE(a.strides() == vector<unsigned>{10, 5});
            }
        }
    }
}
