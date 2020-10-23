#define CATCH_CONFIG_MAIN
#include <vector>

#include "../../catch2/catch.hpp"

#include "../../../core/include/ndarray.hpp"
#include "../../include/data_generator.hpp"


using namespace std;

DataGenerator data_generator;


/**********************************************************************************************
 *                             Operator +, += test scenarios                                  *
**********************************************************************************************/
SCENARIO( "ndarray operator + ", "[ndarray]" ) {
    float *data_a_aligned = data_generator.arange(27);
    float *data_b_aligned = data_generator.arange(27);
    float data_c1_aligned[27] = {
        0., 2., 4., 6., 8., 10., 12., 14., 16., 18.,
        20., 22., 24., 26., 28., 30., 32., 34., 36.,
        38., 40., 42., 44., 46., 48., 50., 52.
    };
    float data_c2_aligned[27] = {
        1., 2., 3., 4., 5., 6., 7., 8., 9., 10., 11.,
        12., 13., 14., 15., 16., 17., 18., 19., 20.,
        21., 22., 23., 24., 25., 26., 27.
    };
    ndarray<float> c1_gt(data_c1_aligned, {3, 3, 3});
    ndarray<float> c2_gt(data_c2_aligned, {3, 3, 3});

    GIVEN("two aligned ndarrays a and b") {
        ndarray<float> a(data_a_aligned, {3, 3, 3});
        ndarray<float> b(data_b_aligned, {3, 3, 3});
        WHEN("a + b is calculated") {
            ndarray<float> c = a + b;
            THEN("correct result c is returned") {
                bool e = c.equals(c1_gt);
                REQUIRE(e == true);
            }
        }
    }
    GIVEN("two aligned ndarrays a and b") {
        ndarray<float> a(data_a_aligned, {3, 3, 3});
        ndarray<float> b(data_b_aligned, {3, 3, 3});
        WHEN("a += b is calculated") {
            a += b;
            THEN("correct result is stored in a") {
                bool e = a.equals(c1_gt);
                REQUIRE(e == true);
            }
        }
    }
    GIVEN("ndarray a and scalar s") {
        ndarray<float> a(data_a_aligned, {3, 3, 3});
        float s = 1;
        WHEN("a += s is calculated") {
            a += s;
            THEN("correct result is stored in a") {
                bool e = a.equals(c2_gt);
                REQUIRE(e == true);
            }
        }
    }


    GIVEN("ndarray a with shape (2, 3, 4, 5) and ndarray b with shape (5,)") {
        float *data_a_unaligned = data_generator.arange(120);
        float *data_b_unaligned = data_generator.arange(5);
        float c_gt_data[120] = {
            0, 2, 4, 6, 8, 5, 7, 9, 11, 13, 10, 12, 14, 16, 18, 15, 17, 19,
            21, 23, 20, 22, 24, 26, 28, 25, 27, 29, 31, 33, 30, 32, 34, 36,
            38, 35, 37, 39, 41, 43, 40, 42, 44, 46, 48, 45, 47, 49, 51, 53,
            50, 52, 54, 56, 58, 55, 57, 59, 61, 63, 60, 62, 64, 66, 68, 65,
            67, 69, 71, 73, 70, 72, 74, 76, 78, 75, 77, 79, 81, 83, 80, 82,
            84, 86, 88, 85, 87, 89, 91, 93, 90, 92, 94, 96, 98, 95, 97, 99,
            101, 103, 100, 102, 104, 106, 108, 105, 107, 109, 111, 113, 110,
            112, 114, 116, 118, 115, 117, 119, 121, 123
        };
        ndarray<float> c_gt(c_gt_data, {2, 3, 4, 5});
        WHEN("c = a + b is calculated") {
            ndarray<float> a(data_a_unaligned, {2, 3, 4, 5});
            ndarray<float> b(data_b_unaligned, {5});
            ndarray<float> c = a + b;
            THEN("correct result is stored in c with shape (2, 3, 4, 5)") {
                bool e = c.equals(c_gt);
                REQUIRE(e == true);
            }
        }
    }
    GIVEN("ndarray a with shape (4, 5) and ndarray b with shape (2, 3, 4, 5)") {
        float *data_a_unaligned = data_generator.arange(20);
        float *data_b_unaligned = data_generator.arange(120);
        float c_gt_data[120] = {
            0, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30, 32, 34,
            36, 38,20, 22, 24, 26, 28, 30, 32, 34, 36, 38, 40, 42, 44, 46, 48,
            50, 52, 54, 56, 58, 40, 42, 44, 46, 48, 50, 52, 54, 56, 58, 60, 62,
            64, 66, 68, 70, 72, 74, 76, 78, 60, 62, 64, 66, 68, 70, 72, 74, 76,
            78, 80, 82, 84, 86, 88, 90, 92, 94, 96, 98, 80, 82, 84, 86, 88, 90,
            92, 94, 96, 98, 100, 102, 104, 106, 108, 110, 112, 114, 116, 118,
            100, 102, 104, 106, 108, 110, 112, 114, 116, 118, 120, 122, 124,
            126, 128, 130, 132, 134, 136, 138
        };
        ndarray<float> c_gt(c_gt_data, {2, 3, 4, 5});
        WHEN("c = a + b is calculated") {
            ndarray<float> a(data_a_unaligned, {4, 5});
            ndarray<float> b(data_b_unaligned, {2, 3, 4, 5});
            ndarray<float> c = a + b;
            THEN("correct result is stored in c with shape (2, 3, 4, 5)") {
                bool e = c.equals(c_gt);
                REQUIRE(e == true);
            }
        }
    }
    GIVEN("ndarray a with shape (1, 4, 5) and ndarray b with shape (2, 3, 1, 1)") {
        float *data_a_unaligned = data_generator.arange(20);
        float *data_b_unaligned = data_generator.arange(6);
        float c_gt_data[120] = {
            0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
            1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20,
            2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21,
            3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22,
            4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23,
            5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24
        };
        ndarray<float> c_gt(c_gt_data, {2, 3, 4, 5});
        WHEN("c = a + b is calculated") {
            ndarray<float> a(data_a_unaligned, {1, 4, 5});
            ndarray<float> b(data_b_unaligned, {2, 3, 1, 1});
            ndarray<float> c = a + b;
            THEN("correct result is stored in c with shape (2, 3, 4, 5)") {
                bool e = c.equals(c_gt);
                REQUIRE(e == true);
            }
        }
    }
    GIVEN("ndarray a with shape (3, 4, 5) and ndarray b with shape (2, 1, 1, 1)") {
        float *data_a_unaligned = data_generator.arange(60);
        float *data_b_unaligned = data_generator.arange(2);
        float c_gt_data[120] = {
            0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
            20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36,
            37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53,
            54, 55, 56, 57, 58, 59, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13,
            14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30,
            31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47,
            48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60
        };
        ndarray<float> c_gt(c_gt_data, {2, 3, 4, 5});
        WHEN("c = a + b is calculated") {
            ndarray<float> a(data_a_unaligned, {3, 4, 5});
            ndarray<float> b(data_b_unaligned, {2, 1, 1, 1});
            ndarray<float> c = a + b;
            THEN("correct result is stored in c with shape (2, 3, 4, 5)") {
                bool e = c.equals(c_gt);
                c.print();
                REQUIRE(e == true);
            }
        }
    }
}
/**********************************************************************************************/

/**********************************************************************************************
 *                             Operator -, -= test scenarios                                  *
**********************************************************************************************/
SCENARIO( "ndarray operator - ", "[ndarray]" ) {
    float *data_a_aligned = data_generator.arange(27);
    float *data_b_aligned = data_generator.arange(27);
    float data_c1_aligned[27] = {0};
    float data_c2_aligned[27] = {
        -1., -1., -1., -1., -1., -1., -1., -1., -1.,
        -1., -1., -1., -1., -1., -1., -1., -1., -1.,
        -1., -1., -1., -1., -1., -1., -1., -1., -1.
    };
    ndarray<float> c1_gt(data_c1_aligned, {3, 3, 3});
    ndarray<float> c2_gt(data_c2_aligned, {3, 3, 3});

    GIVEN("two aligned ndarrays a and b") {
        ndarray<float> a(data_a_aligned, {3, 3, 3});
        ndarray<float> b(data_b_aligned, {3, 3, 3});
        WHEN("a - b is calculated") {
            ndarray<float> c = a - b;
            THEN("correct result c is returned") {
                bool e = c.equals(c1_gt);
                REQUIRE(e == true);
            }
        }
    }
    GIVEN("two aligned ndarrays a and b") {
        ndarray<float> a(data_a_aligned, {3, 3, 3});
        ndarray<float> b(data_b_aligned, {3, 3, 3});
        WHEN("a -= b is calculated") {
            a -= b;
            THEN("correct result is stored in a") {
                bool e = a.equals(c1_gt);
                REQUIRE(e == true);
            }
        }
    }
    GIVEN("ndarray a and scalar s") {
        ndarray<float> a({3, 3, 3});
        float s = 1;
        WHEN("a -= s is calculated") {
            a -= s;
            THEN("correct result is stored in a") {
                bool e = a.equals(c2_gt);
                a.print();
                REQUIRE(e == true);
            }
        }
    }

//
//    GIVEN("ndarray a with shape (2, 3, 4, 5) and ndarray b with shape (5,)") {
//        float *data_a_unaligned = data_generator.arange(120);
//        float *data_b_unaligned = data_generator.arange(5);
//        float c_gt_data[120] = {
//
//        };
//        ndarray<float> c_gt(c_gt_data, {2, 3, 4, 5});
//        WHEN("c = a - b is calculated") {
//            ndarray<float> a(data_a_unaligned, {2, 3, 4, 5});
//            ndarray<float> b(data_b_unaligned, {5});
//            ndarray<float> c = a - b;
//            THEN("correct result is stored in c with shape (2, 3, 4, 5)") {
//                bool e = c.equals(c_gt);
//                REQUIRE(e == true);
//            }
//        }
//    }
//    GIVEN("ndarray a with shape (4, 5) and ndarray b with shape (2, 3, 4, 5)") {
//        float *data_a_unaligned = data_generator.arange(20);
//        float *data_b_unaligned = data_generator.arange(120);
//        float c_gt_data[120] = {
//
//        };
//        ndarray<float> c_gt(c_gt_data, {2, 3, 4, 5});
//        WHEN("c = a - b is calculated") {
//            ndarray<float> a(data_a_unaligned, {4, 5});
//            ndarray<float> b(data_b_unaligned, {2, 3, 4, 5});
//            ndarray<float> c = a - b;
//            THEN("correct result is stored in c with shape (2, 3, 4, 5)") {
//                bool e = c.equals(c_gt);
//                REQUIRE(e == true);
//            }
//        }
//    }
//    GIVEN("ndarray a with shape (1, 4, 5) and ndarray b with shape (2, 3, 1, 1)") {
//        float *data_a_unaligned = data_generator.arange(20);
//        float *data_b_unaligned = data_generator.arange(6);
//        float c_gt_data[120] = {
//
//        };
//        ndarray<float> c_gt(c_gt_data, {2, 3, 4, 5});
//        WHEN("c = a - b is calculated") {
//            ndarray<float> a(data_a_unaligned, {1, 4, 5});
//            ndarray<float> b(data_b_unaligned, {2, 3, 1, 1});
//            ndarray<float> c = a - b;
//            THEN("correct result is stored in c with shape (2, 3, 4, 5)") {
//                bool e = c.equals(c_gt);
//                REQUIRE(e == true);
//            }
//        }
//    }
//    GIVEN("ndarray a with shape (3, 4, 5) and ndarray b with shape (2, 1, 1, 1)") {
//        float *data_a_unaligned = data_generator.arange(60);
//        float *data_b_unaligned = data_generator.arange(2);
//        float c_gt_data[120] = {
//
//        };
//        ndarray<float> c_gt(c_gt_data, {2, 3, 4, 5});
//        WHEN("c = a - b is calculated") {
//            ndarray<float> a(data_a_unaligned, {3, 4, 5});
//            ndarray<float> b(data_b_unaligned, {2, 1, 1, 1});
//            ndarray<float> c = a - b;
//            THEN("correct result is stored in c with shape (2, 3, 4, 5)") {
//                bool e = c.equals(c_gt);
//                c.print();
//                REQUIRE(e == true);
//            }
//        }
//    }
}
/**********************************************************************************************/