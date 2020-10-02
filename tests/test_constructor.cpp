#include <vector>

#include "catch.hpp"

#include "../src/ndarray.hpp"
#include "data.hpp"


using namespace std;


/***********************************************************************************************
 *                          Constructor test scenarios                                         *
 **********************************************************************************************/
SCENARIO( "ndarray construction", "[ndarray]" ) {
    GIVEN( "1d data stored as 1d array and its shape" ) {
        ndarray<float> a1d(test_data->a1d_data, test_data->a1d_shape);

        WHEN("ndarray is constructed") {
            THEN("data is assigned, dimension, size and shape products are calculated") {
                vector<float> assigned_data(a1d.data, a1d.data + 3);
                vector<float> given_data(test_data->a1d_data, test_data->a1d_data + 3);

                REQUIRE(a1d.dim == 1);
                REQUIRE(a1d.size == 3);
                REQUIRE(a1d.shape_products == vector<unsigned >{3});
                REQUIRE(assigned_data == given_data);
            }
        }
    }

    GIVEN( "2d data stored as 1d array and its shape" ) {
        ndarray<float> a2d(test_data->a2d_data, test_data->a2d_shape);

        WHEN("ndarray is constructed") {
            THEN("data is assigned, dimension, size and shape products are calculated") {
                vector<float> assigned_data(a2d.data, a2d.data + 16);
                vector<float> given_data(test_data->a2d_data, test_data->a2d_data + 16);

                REQUIRE(a2d.dim == 2);
                REQUIRE(a2d.size == 16);
                REQUIRE(a2d.shape_products == vector<unsigned >{4});
                REQUIRE(assigned_data == given_data);
            }
        }
    }

    GIVEN( "3d data stored as 1d array and its shape" ) {
        ndarray<float> a3d(test_data->a3d_data, test_data->a3d_shape);

        WHEN("ndarray is constructed") {
            THEN("data is assigned, dimension, size and shape products are calculated") {
                vector<float> assigned_data(a3d.data, a3d.data + 30);
                vector<float> given_data(test_data->a3d_data, test_data->a3d_data + 30);

                REQUIRE(a3d.dim == 3);
                REQUIRE(a3d.size == 30);
                REQUIRE(a3d.shape_products == vector<unsigned >{10, 5});
                REQUIRE(assigned_data == given_data);
            }
        }
    }

    GIVEN( "4d data stored as 1d array and its shape" ) {
        ndarray<float> a4d(test_data->a4d_data, test_data->a4d_shape);

        WHEN("ndarray is constructed") {
            THEN("data is assigned, dimension, size and shape products are calculated") {
                vector<float> assigned_data(a4d.data, a4d.data + 120);
                vector<float> given_data(test_data->a4d_data, test_data->a4d_data + 120);

                REQUIRE(a4d.dim == 4);
                REQUIRE(a4d.size == 120);
                REQUIRE(a4d.shape_products == vector<unsigned >{30, 10, 5});
                REQUIRE(assigned_data == given_data);
            }
        }
    }

    // TODO test and implement init with 0 when no data is given
}
/**********************************************************************************************/