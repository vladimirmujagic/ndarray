#include <vector>

#include "catch.hpp"

#include "../src/ndarray.hpp"
#include "data.hpp"


using namespace std;


/**********************************************************************************************
*                         View sub-array without copy test scenarios                          *
***********************************************************************************************/
SCENARIO( "ndarray view", "[ndarray]" ) {
    GIVEN("2d array and index i") {
        ndarray<float> a2d(test_data->a2d_data, test_data->a2d_shape);

        WHEN("array is viewed at index i") {
            ndarray<float> a1d = a2d.view({1});

            THEN("1d array is returned") {
                REQUIRE(vector<float>(a1d.data, a1d.data + a1d.size)== vector<float>{4., 5., 6., 7.});
            }
        }
    }

    GIVEN("3d array and index i") {
        ndarray<float> a3d(test_data->a3d_data, test_data->a3d_shape);
        float gt_data[10] = {10, 11, 12, 13, 14, 15, 16, 17, 18, 19};
        ndarray<float> a2d_gt(gt_data, {2, 5});

        WHEN("array is viewed at index i") {
            ndarray<float> a2d = a3d.view({1});
            bool r = a2d == a2d_gt;
            THEN("2d array is returned") {
                REQUIRE(r == true);
            }
        }
    }
}
/**********************************************************************************************/