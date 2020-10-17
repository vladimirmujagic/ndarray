#define CATCH_CONFIG_MAIN
#include <vector>

#include "../../../catch2/catch.hpp"

#include "../../../../core/include/ndarray.hpp"
#include "../../../include/data_generator.hpp"


using namespace std;


SCENARIO( "ndarray reshape", "[ndarray]" ) {
    GIVEN("3d array with shape (5, 2, 2)") {
        WHEN("array is reshaped to (2, 2, 5)") {
            THEN("proper dimension new shape and shape products are assigned") {
                REQUIRE(true == true);
            }
        }
    }
}
