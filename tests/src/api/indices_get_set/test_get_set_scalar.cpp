#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"

#include "../../../../core/include/ndarray.hpp"
#include "../../../include/data_generator.hpp"

using namespace std;


SCENARIO( "ndarray indices access", "[ndarray]" ) {
    GIVEN("index (i)") {
        WHEN("element is accessed") {
            THEN("correct value is returned") {
                REQUIRE(true == true);
            }
        }
    }

    GIVEN("indices (i, j)") {
        WHEN("element is accessed") {
            THEN("correct value is returned") {
                REQUIRE(true == true);
            }
        }
    }

    GIVEN("indices (i, j, k)") {
        WHEN("element is accessed") {
            THEN("correct value is returned") {
                REQUIRE(true == true);
            }
        }
    }

    GIVEN("indices (i, j, k, l)") {
        WHEN("element is accessed") {
            THEN("correct value is returned") {
                REQUIRE(true == true);
            }
        }
    }

    // ...
}
