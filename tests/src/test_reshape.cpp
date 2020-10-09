#define CATCH_CONFIG_MAIN

#include <vector>

#include "../catch2/catch.hpp"

#include "../../core/include/ndarray.hpp"
#include "../include/data.hpp"


using namespace std;


/**********************************************************************************************
*                         Reshape test scenarios                                              *
***********************************************************************************************/
SCENARIO( "ndarray reshape", "[ndarray]" ) {
    GIVEN("3d array with shape (5, 2, 2)") {
        float data[20] = {0.};
        for(unsigned i = 0; i < 20; i++) { data[i] = (float)i; }

        ndarray<float> a(data, {5, 2, 2});

        WHEN("array is reshaped to (2, 2, 5)") {
            a.reshape({2, 2, 5});
            cout << a << endl;
            THEN("proper dimension new shape and shape products are assigned") {
                REQUIRE(a.shape == vector<unsigned> {2, 2, 5});
                REQUIRE(a.dim == 3);
                REQUIRE(a.shape_products == vector<unsigned> {10, 5});
            }
        }
    }
}
/**********************************************************************************************/