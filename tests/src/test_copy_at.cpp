#define CATCH_CONFIG_MAIN
#include "../catch2/catch.hpp"

#include <vector>

#include "../../core/include/ndarray.hpp"
#include "../include/data.hpp"

using namespace std;


/**********************************************************************************************
*                             Copy sub-array test scenarios                                   *
***********************************************************************************************/
SCENARIO( "ndarray copy", "[ndarray]" ) {
    GIVEN("2d array and index i") {
        ndarray<float> a2d(test_data->a2d_data, test_data->a2d_shape);

        WHEN("array is viewed at index i") {
            ndarray<float> a1d = a2d.copy_at({2});
            float gt_data[4] = {8, 9, 10, 11};
            ndarray<float> a1d_gt(gt_data, {4});
            bool r = a1d == a1d_gt;

            a1d(0) = 111.;

            THEN("1d array copy is returned") {
                REQUIRE(r == true);
                REQUIRE(a1d(0) != a2d(2, 0));
            }
        }
    }

    GIVEN("3d array and index i") {
        ndarray<float> a3d(test_data->a3d_data, test_data->a3d_shape);

        WHEN("array is viewed at index i") {
            ndarray<float> a2d = a3d.copy_at({0});
            float gt_data[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
            ndarray<float> a2d_gt(gt_data, {2, 5});
            bool r = a2d == a2d_gt;

            a2d(0, 0) = 111.;

            THEN("2d array copy is returned") {
                REQUIRE(r == true);
                REQUIRE(a3d(0, 0, 0) != a2d(0, 0));
            }
        }
    }
}
/**********************************************************************************************/

