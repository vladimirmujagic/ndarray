#define CATCH_CONFIG_MAIN
#include <vector>

#include "catch.hpp"

#include "../src/ndarray.hpp"
#include "data.hpp"


using namespace std;


/**********************************************************************************************
 *                             Operator == test scenarios                                     *
**********************************************************************************************/
SCENARIO( "ndarray operator == ", "[ndarray]" ) {
    GIVEN("two equivalent ndarrays a1 and a2") {
        ndarray<float> a1(test_data->a2d_data, test_data->a2d_shape);
        ndarray<float> a2(test_data->a2d_data, test_data->a2d_shape);

        WHEN("they are compared") {
            bool r = a1 == a2;
            THEN("value true is returned") {
                REQUIRE(r == true);
            }
        }
    }
}
/**********************************************************************************************/


/**********************************************************************************************
 *                             Operator +, += test scenarios                                  *
**********************************************************************************************/
SCENARIO( "ndarray operator + ", "[ndarray]" ) {
    GIVEN("two ndarrays a1 and a2") {
        ndarray<float> a1(test_data->a2d_data, test_data->a2d_shape);
        ndarray<float> a2(test_data->a2d_data, test_data->a2d_shape);

        WHEN("addition is performed") {
            ndarray<float> a = a1 + a2;
            float gt_data[16] = {0, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30};
            ndarray<float> a_gt(gt_data, {4, 4});

            bool r = a == a_gt;
            THEN("correct result is returned") {
                REQUIRE(r == true);
            }
        }
    }

    GIVEN("two ndarrays a1 and a2") {
        ndarray<float> a1(test_data->a2d_data, test_data->a2d_shape);
        ndarray<float> a2(test_data->a2d_data, test_data->a2d_shape);

        WHEN("addition is performed") {
            a1 += a2;
            float gt_data[16] = {0, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30};
            ndarray<float> a_gt(gt_data, {4, 4});

            bool r = a1 == a_gt;
            THEN("correct result is returned") {
                REQUIRE(r == true);
            }
        }
    }

    GIVEN("ndarray a1 and scalar s") {
        ndarray<float> a1(test_data->a2d_data, test_data->a2d_shape);
        float s = 1.;

        WHEN("addition is performed") {
            a1 += s;
            float gt_data[16] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29, 31};
            ndarray<float> a_gt(gt_data, {4, 4});

            bool r = a1 == a_gt;
            THEN("correct result is returned") {
                REQUIRE(r == true);
            }
        }
    }
}
/**********************************************************************************************/


/**********************************************************************************************
 *                             Operator -, -= test scenarios                                  *
**********************************************************************************************/
SCENARIO( "ndarray operator - ", "[ndarray]" ) {
    GIVEN("two ndarrays a1 and a2") {
        ndarray<float> a1(test_data->a2d_data, test_data->a2d_shape);
        ndarray<float> a2(test_data->a2d_data, test_data->a2d_shape);

        WHEN("subtraction is performed") {
            ndarray<float> a = a1 - a2;
            float gt_data[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
            ndarray<float> a_gt(gt_data, {4, 4});

            bool r = a == a_gt;
            THEN("correct result is returned") {
                REQUIRE(r == true);
            }
        }
    }

    GIVEN("two ndarrays a1 and a2") {
        ndarray<float> a1(test_data->a2d_data, test_data->a2d_shape);
        ndarray<float> a2(test_data->a2d_data, test_data->a2d_shape);

        WHEN("subtraction is performed") {
            a1 -= a2;
            float gt_data[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
            ndarray<float> a_gt(gt_data, {4, 4});

            bool r = a1 == a_gt;
            THEN("correct result is returned") {
                REQUIRE(r == true);
            }
        }
    }

    GIVEN("ndarray a1 and scalar s") {
        float d[4] = {1., 2., 3., 4.};
        ndarray<float> a1(d, {2, 2});
        float s = 1;
        WHEN("subtraction is performed") {
            a1 -= s;
            THEN("correct result is returned") {
                float d_gt[4] = {0., 1., 2., 3.};
                ndarray<float> a1_gt(d_gt, {2, 2});
                bool r = a1 == a1_gt;
                REQUIRE(r == true);
            }
        }
    }
}

/**********************************************************************************************/


/**********************************************************************************************
 *                             Operator *, *= test scenarios                                  *
**********************************************************************************************/
SCENARIO( "ndarray operator * ", "[ndarray]" ) {
    GIVEN("two ndarrays a1 and a2") {
        float a1_d[4] = {2., 3., 5., 7.};
        ndarray<float> a1(a1_d, {2, 2});
        float a2_d[4] = {1., 4., 8., 12.};
        ndarray<float> a2(a2_d, {2, 2});

        WHEN("multiplication is performed") {
            ndarray<float> a = a1 * a2;

            THEN("correct result is returned") {
                float d_gt[4] = {2., 12., 40., 84.};
                ndarray<float> a_gt(d_gt, {2, 2});
                bool r = a == a_gt;
                REQUIRE(r == true);
            }
        }
    }
}

SCENARIO( "ndarray operator *= array ", "[ndarray]" ) {
    GIVEN("two ndarrays a1 and a2") {
        float a1_d[4] = {2., 3., 5., 7.};
        ndarray<float> a1(a1_d, {2, 2});
        float a2_d[4] = {1., 4., 8., 12.};
        ndarray<float> a2(a2_d, {2, 2});

        WHEN("multiplication is performed") {
            a1 *= a2;

            THEN("correct result is returned") {
                float d_gt[4] = {2., 12., 40., 84.};
                ndarray<float> a_gt(d_gt, {2, 2});
                bool r = a1 == a_gt;
                REQUIRE(r == true);
            }
        }
    }
}

SCENARIO( "ndarray operator *= scalar ", "[ndarray]" ) {
    GIVEN("ndarray a1 and and scalar s") {
        float a1_d[4] = {2., 3., 5., 7.};
        ndarray<float> a1(a1_d, {2, 2});
        float s = 2.;

        WHEN("multiplication is performed") {
            a1 *= s;
            cout << a1 << endl;

            THEN("correct result is returned") {
                float d_gt[4] = {4., 6., 10., 14.};
                ndarray<float> a_gt(d_gt, {2, 2});
                bool r = a1 == a_gt;
                REQUIRE(r == true);
            }
        }
    }
}
/**********************************************************************************************/


/**********************************************************************************************
 *                             Operator /, /= test scenarios                                  *
**********************************************************************************************/
SCENARIO( "ndarray operator / ", "[ndarray]" ) {
    GIVEN("two ndarrays a1 and a2") {
        float a1_d[4] = {2., 8., 40., 24.};
        ndarray<float> a1(a1_d, {2, 2});
        float a2_d[4] = {1., 4., 8., 12.};
        ndarray<float> a2(a2_d, {2, 2});

        WHEN("multiplication is performed") {
            ndarray<float> a = a1 / a2;
            cout << a << endl;
            THEN("correct result is returned") {
                float d_gt[4] = {2., 2., 5., 2.};
                ndarray<float> a_gt(d_gt, {2, 2});
                bool r = a == a_gt;
                REQUIRE(r == true);
            }
        }
    }
}

SCENARIO( "ndarray operator /= array ", "[ndarray]" ) {
    GIVEN("two ndarrays a1 and a2") {
        float a1_d[4] = {2., 8., 40., 24.};
        ndarray<float> a1(a1_d, {2, 2});
        float a2_d[4] = {1., 4., 8., 12.};
        ndarray<float> a2(a2_d, {2, 2});

        WHEN("multiplication is performed") {
            a1 /= a2;

            THEN("correct result is returned") {
                float d_gt[4] = {2., 2., 5., 2.};
                ndarray<float> a_gt(d_gt, {2, 2});
                bool r = a1 == a_gt;
                REQUIRE(r == true);
            }
        }
    }
}

SCENARIO( "ndarray operator /= scalar ", "[ndarray]" ) {
    GIVEN("ndarray a1 and and scalar s") {
        float a1_d[4] = {2., 4., 10., 14.};
        ndarray<float> a1(a1_d, {2, 2});
        float s = 2.;

        WHEN("division is performed") {
            a1 /= s;
            cout << a1 << endl;

            THEN("correct result is returned") {
                float d_gt[4] = {1., 2., 5., 7.};
                ndarray<float> a_gt(d_gt, {2, 2});
                bool r = a1 == a_gt;
                REQUIRE(r == true);
            }
        }
    }
}
/**********************************************************************************************/