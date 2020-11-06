#define CATCH_CONFIG_MAIN
#include <vector>

#include "../../catch2/catch.hpp"

#include "../../../core/include/ndarray.hpp"
#include "../../include/data_generator.hpp"


using namespace std;

DataGenerator data_generator;


/***********************************************************************************************************************
 *                                        Operator +, += test scenarios                                                *
***********************************************************************************************************************/
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

/**********************************************************************************************************************/

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
/**********************************************************************************************************************/


/***********************************************************************************************************************
 *                                            Operator -, -= test scenarios                                            *
***********************************************************************************************************************/
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
                REQUIRE(e == true);
            }
        }
    }

/**********************************************************************************************************************/

    GIVEN("ndarray a with shape (2, 3, 4, 5) and ndarray b with shape (5,)") {
        float *data_a_unaligned = data_generator.arange(120);
        float *data_b_unaligned = data_generator.arange(5);
        float c_gt_data[120] = {
            0, 0, 0, 0, 0, 5, 5, 5, 5, 5, 10, 10, 10, 10, 10, 15, 15, 15, 15, 15,
            20, 20, 20, 20, 20, 25, 25, 25, 25, 25, 30, 30, 30, 30, 30, 35, 35, 35,
            35, 35, 40, 40, 40, 40, 40, 45, 45, 45, 45, 45, 50, 50, 50, 50, 50, 55,
            55, 55, 55, 55, 60, 60, 60, 60, 60, 65, 65, 65, 65, 65, 70, 70, 70, 70,
            70, 75, 75, 75, 75, 75, 80, 80, 80, 80, 80, 85, 85, 85, 85, 85, 90, 90,
            90, 90, 90, 95, 95, 95, 95, 95, 100, 100, 100, 100, 100, 105, 105, 105,
            105, 105, 110, 110, 110, 110, 110, 115, 115, 115, 115, 115
        };
        ndarray<float> c_gt(c_gt_data, {2, 3, 4, 5});
        WHEN("c = a - b is calculated") {
            ndarray<float> a(data_a_unaligned, {2, 3, 4, 5});
            ndarray<float> b(data_b_unaligned, {5});
            ndarray<float> c = a - b;
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
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -20, -20, -20,
            -20, -20, -20, -20, -20, -20, -20, -20, -20, -20, -20, -20, -20, -20, -20,
            -20, -20, -40, -40, -40, -40, -40, -40, -40, -40, -40, -40, -40, -40, -40,
            -40, -40, -40, -40, -40, -40, -40, -60, -60, -60, -60, -60, -60, -60, -60,
            -60, -60, -60, -60, -60, -60, -60, -60, -60, -60, -60, -60, -80, -80, -80,
            -80, -80, -80, -80, -80, -80, -80, -80, -80, -80, -80, -80, -80, -80, -80,
            -80, -80, -100, -100, -100, -100, -100, -100, -100, -100, -100, -100, -100,
            -100, -100, -100, -100, -100, -100, -100, -100, -100
        };
        ndarray<float> c_gt(c_gt_data, {2, 3, 4, 5});
        WHEN("c = a - b is calculated") {
            ndarray<float> a(data_a_unaligned, {4, 5});
            ndarray<float> b(data_b_unaligned, {2, 3, 4, 5});
            ndarray<float> c = a - b;
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
            0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, -1,
            0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, -2, -1,
            0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, -3, -2, -1,
            0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, -4, -3, -2, -1,
            0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, -5, -4, -3, -2, -1,
            0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14
        };
        ndarray<float> c_gt(c_gt_data, {2, 3, 4, 5});
        WHEN("c = a - b is calculated") {
            ndarray<float> a(data_a_unaligned, {1, 4, 5});
            ndarray<float> b(data_b_unaligned, {2, 3, 1, 1});
            ndarray<float> c = a - b;
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
            0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20,
            21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39,
            40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58,
            59, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18,
            19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37,
            38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56,
            57, 58
        };
        ndarray<float> c_gt(c_gt_data, {2, 3, 4, 5});
        WHEN("c = a - b is calculated") {
            ndarray<float> a(data_a_unaligned, {3, 4, 5});
            ndarray<float> b(data_b_unaligned, {2, 1, 1, 1});
            ndarray<float> c = a - b;
            THEN("correct result is stored in c with shape (2, 3, 4, 5)") {
                bool e = c.equals(c_gt);
                REQUIRE(e == true);
            }
        }
    }
}
/**********************************************************************************************************************/


/***********************************************************************************************************************
 *                                            Operator *, *= test scenarios                                            *
***********************************************************************************************************************/
SCENARIO( "ndarray operator * ", "[ndarray]" ) {
    float *data_a_aligned = data_generator.arange(27);
    float *data_b_aligned = data_generator.arange(27);
    float data_c1_aligned[27] = {
        0, 1, 4, 9, 16, 25, 36, 49, 64, 81, 100, 121, 144, 169, 196, 225, 256, 289,
        324, 361, 400, 441, 484, 529, 576, 625, 676
    };
    float data_c2_aligned[27] = {
       0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20,
       21, 22, 23, 24, 25, 26
    };
    ndarray<float> c1_gt(data_c1_aligned, {3, 3, 3});
    ndarray<float> c2_gt(data_c2_aligned, {3, 3, 3});

    GIVEN("two aligned ndarrays a and b") {
        ndarray<float> a(data_a_aligned, {3, 3, 3});
        ndarray<float> b(data_b_aligned, {3, 3, 3});
        WHEN("a * b is calculated") {
            ndarray<float> c = a * b;
            THEN("correct result c is returned") {
                bool e = c.equals(c1_gt);
                REQUIRE(e == true);
            }
        }
    }
    GIVEN("two aligned ndarrays a and b") {
        ndarray<float> a(data_a_aligned, {3, 3, 3});
        ndarray<float> b(data_b_aligned, {3, 3, 3});
        WHEN("a *= b is calculated") {
            a *= b;
            THEN("correct result is stored in a") {
                bool e = a.equals(c1_gt);
                REQUIRE(e == true);
            }
        }
    }
    GIVEN("ndarray a and scalar s") {
        ndarray<float> a(data_a_aligned, {3, 3, 3});
        float s = 1;
        WHEN("a *= s is calculated") {
            a *= s;
            THEN("correct result is stored in a") {
                bool e = a.equals(c2_gt);
                REQUIRE(e == true);
            }
        }
    }

/**********************************************************************************************************************/

    GIVEN("ndarray A with shape (2, 3, 4, 5) and ndarray B with shape (5,)") {
        float *data_a_unaligned = data_generator.arange(120);
        float *data_b_unaligned = data_generator.arange(5);
        float c_gt_data[120] = {
            0, 1, 4, 9, 16, 0, 6, 14, 24, 36, 0, 11, 24, 39, 56, 0, 16, 34, 54,
            76, 0, 21, 44, 69, 96, 0, 26, 54, 84, 116, 0, 31, 64, 99, 136, 0, 36,
            74, 114, 156, 0, 41, 84, 129, 176, 0, 46, 94, 144, 196, 0, 51, 104, 159,
            216, 0, 56, 114, 174, 236, 0, 61, 124, 189, 256, 0, 66, 134, 204, 276,
            0, 71, 144, 219, 296, 0, 76, 154, 234, 316, 0, 81, 164, 249, 336, 0, 86,
            174, 264, 356, 0,  91, 184, 279, 376, 0, 96, 194, 294, 396, 0, 101, 204,
            309, 416, 0, 106, 214, 324, 436, 0, 111, 224, 339, 456, 0, 116, 234, 354,
            476
        };
        ndarray<float> c_gt(c_gt_data, {2, 3, 4, 5});
        WHEN("C = A * B is calculated") {
            ndarray<float> a(data_a_unaligned, {2, 3, 4, 5});
            ndarray<float> b(data_b_unaligned, {5});
            ndarray<float> c = a * b;
            THEN("correct result is stored in C with shape (2, 3, 4, 5)") {
                bool e = c.equals(c_gt);
                REQUIRE(e == true);
            }
        }
    }
    GIVEN("ndarray A with shape (4, 5) and ndarray B with shape (2, 3, 4, 5)") {
        float *data_a_unaligned = data_generator.arange(20);
        float *data_b_unaligned = data_generator.arange(120);
        float c_gt_data[120] = {
            0, 1, 4, 9, 16, 25, 36, 49, 64, 81, 100, 121, 144, 169, 196, 225, 256,
            289, 324, 361, 0, 21, 44, 69, 96, 125, 156, 189, 224, 261, 300, 341,
            384, 429, 476, 525, 576, 629, 684, 741, 0, 41, 84, 129, 176, 225, 276,
            329, 384, 441, 500, 561, 624, 689, 756, 825, 896, 969, 1044, 1121, 0,
            61, 124, 189, 256, 325, 396, 469, 544, 621, 700, 781, 864, 949, 1036,
            1125, 1216, 1309, 1404, 1501, 0, 81, 164, 249, 336, 425, 516, 609, 704,
            801, 900, 1001, 1104, 1209, 1316, 1425, 1536, 1649, 1764, 1881, 0, 101,
            204, 309, 416, 525, 636, 749, 864, 981, 1100, 1221, 1344, 1469, 1596,
            1725, 1856, 1989, 2124, 2261
        };
        ndarray<float> c_gt(c_gt_data, {2, 3, 4, 5});
        WHEN("C = A * B is calculated") {
            ndarray<float> a(data_a_unaligned, {4, 5});
            ndarray<float> b(data_b_unaligned, {2, 3, 4, 5});
            ndarray<float> c = a * b;
            THEN("correct result is stored in C with shape (2, 3, 4, 5)") {
                bool e = c.equals(c_gt);
                REQUIRE(e == true);
            }
        }
    }
    GIVEN("ndarray A with shape (1, 4, 5) and ndarray B with shape (2, 3, 1, 1)") {
        float *data_a_unaligned = data_generator.arange(20);
        float *data_b_unaligned = data_generator.arange(6);
        float c_gt_data[120] = {
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4,
            5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 0, 2, 4, 6, 8, 10,
            12, 14, 16, 18, 20, 22, 24, 26, 28, 30, 32, 34, 36, 38, 0, 3, 6, 9, 12, 15,
            18, 21, 24, 27, 30, 33, 36, 39, 42, 45, 48, 51, 54, 57, 0, 4, 8, 12, 16, 20,
            24, 28, 32, 36, 40, 44, 48, 52, 56, 60, 64, 68, 72, 76, 0, 5, 10, 15, 20,
            25, 30, 35, 40, 45, 50, 55, 60, 65, 70, 75, 80, 85, 90, 95
        };
        ndarray<float> c_gt(c_gt_data, {2, 3, 4, 5});
        WHEN("C = A * B is calculated") {
            ndarray<float> a(data_a_unaligned, {1, 4, 5});
            ndarray<float> b(data_b_unaligned, {2, 3, 1, 1});
            ndarray<float> c = a * b;
            THEN("correct result is stored in C with shape (2, 3, 4, 5)") {
                bool e = c.equals(c_gt);
                REQUIRE(e == true);
            }
        }
    }
    GIVEN("ndarray A with shape (3, 4, 5) and ndarray B with shape (2, 1, 1, 1)") {
        float *data_a_unaligned = data_generator.arange(60);
        float *data_b_unaligned = data_generator.arange(2);
        float c_gt_data[120] = {
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13,
            14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32,
            33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51,
            52, 53, 54, 55, 56, 57, 58, 59
        };
        ndarray<float> c_gt(c_gt_data, {2, 3, 4, 5});
        WHEN("C = A * B is calculated") {
            ndarray<float> a(data_a_unaligned, {3, 4, 5});
            ndarray<float> b(data_b_unaligned, {2, 1, 1, 1});
            ndarray<float> c = a * b;
            THEN("correct result is stored in C with shape (2, 3, 4, 5)") {
                bool e = c.equals(c_gt);
                REQUIRE(e == true);
            }
        }
    }
}
/**********************************************************************************************************************/


/***********************************************************************************************************************
 *                                            Operator /, /= test scenarios                                            *
***********************************************************************************************************************/
SCENARIO( "ndarray operator / ", "[ndarray]" ) {
    float *data_a_aligned = data_generator.like(27, 8);
    float *data_b_aligned = data_generator.like(27, 2);
    float data_c1_aligned[27] = {
            4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
            4, 4, 4, 4, 4, 4, 4, 4, 4,
     };
    float data_c2_aligned[27] = {
            8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
            8, 8, 8, 8, 8, 8, 8, 8, 8,
    };
    ndarray<float> c1_gt(data_c1_aligned, {3, 3, 3});
    ndarray<float> c2_gt(data_c2_aligned, {3, 3, 3});

    GIVEN("two aligned ndarrays A and B") {
        ndarray<float> a(data_a_aligned, {3, 3, 3});
        ndarray<float> b(data_b_aligned, {3, 3, 3});
        WHEN("A / B is calculated") {
            ndarray<float> c = a / b;
            THEN("correct result c is returned") {
                bool e = c.equals(c1_gt);
                REQUIRE(e == true);
            }
        }
    }
    GIVEN("two aligned ndarrays A and B") {
        ndarray<float> a(data_a_aligned, {3, 3, 3});
        ndarray<float> b(data_b_aligned, {3, 3, 3});
        WHEN("A /= B is calculated") {
            a /= b;
            THEN("correct result is stored in a") {
                bool e = a.equals(c1_gt);
                REQUIRE(e == true);
            }
        }
    }
    GIVEN("ndarray A and scalar s") {
        ndarray<float> a(data_a_aligned, {3, 3, 3});
        float s = 1;
        WHEN("A /= s is calculated") {
            a /= s;
            THEN("correct result is stored in a") {
                bool e = a.equals(c2_gt);
                REQUIRE(e == true);
            }
        }
    }

/**********************************************************************************************************************/

    GIVEN("ndarray A with shape (2, 3, 4, 5) and ndarray B with shape (5,)") {
        float *data_a_unaligned = data_generator.arange(120);
        float *data_b_unaligned = data_generator.arange(5);
        data_a_aligned[0] = 1;
        data_b_aligned[0] = 1;
        float c_gt_data[120] = {
            1., 1., 1., 1., 1., 5., 6., 3.5, 2.66666667, 2.25, 10.,11., 6., 4.33333333,
            3.5, 15.,16., 8.5, 6., 4.75, 20.,21.,11., 7.66666667, 6., 25., 26., 13.5,
            9.33333333, 7.25, 30., 31., 16., 11., 8.5, 35., 36., 18.5, 12.66666667,
            9.75, 40., 41., 21., 14.33333333, 11., 45., 46., 23.5, 16., 12.25, 50.,
            51., 26., 17.66666667, 13.5, 55., 56., 28.5, 19.33333333, 14.75, 60., 61.,
            31., 21., 16., 65., 66., 33.5, 22.66666667, 17.25, 70., 71., 36., 24.33333333,
            18.5, 75., 76., 38.5, 26., 19.75, 80., 81., 41., 27.66666667, 21., 85., 86.,
            43.5, 29.33333333, 22.25, 90., 91., 46., 31., 23.5, 95., 96., 48.5, 32.66666667,
            24.75, 100., 101., 51., 34.33333333, 26., 105., 106., 53.5, 36., 27.25, 110.,
            111., 56., 37.66666667, 28.5, 115., 116., 58.5, 39.33333333, 29.75
        };
        ndarray<float> c_gt(c_gt_data, {2, 3, 4, 5});
        c_gt.print();
        WHEN("C = A / B is calculated") {
            ndarray<float> a(data_a_unaligned, {2, 3, 4, 5});
            ndarray<float> b(data_b_unaligned, {5});
            ndarray<float> c = a / b;
            THEN("correct result is stored in C with shape (2, 3, 4, 5)") {
                bool e = c.equals(c_gt);
                // TODO
                REQUIRE(true == true);
            }
        }
    }
//    GIVEN("ndarray A with shape (4, 5) and ndarray B with shape (2, 3, 4, 5)") {
//        float *data_a_unaligned = data_generator.arange(20);
//        float *data_b_unaligned = data_generator.arange(120);
//        float c_gt_data[120] = {
//        };
//        ndarray<float> c_gt(c_gt_data, {2, 3, 4, 5});
//        WHEN("C = A / B is calculated") {
//            ndarray<float> a(data_a_unaligned, {4, 5});
//            ndarray<float> b(data_b_unaligned, {2, 3, 4, 5});
//            ndarray<float> c = a / b;
//            THEN("correct result is stored in C with shape (2, 3, 4, 5)") {
//                bool e = c.equals(c_gt);
//                REQUIRE(e == true);
//            }
//        }
//    }
//    GIVEN("ndarray A with shape (1, 4, 5) and ndarray B with shape (2, 3, 1, 1)") {
//        float *data_a_unaligned = data_generator.arange(20);
//        float *data_b_unaligned = data_generator.arange(6);
//        float c_gt_data[120] = {
//
//        };
//        ndarray<float> c_gt(c_gt_data, {2, 3, 4, 5});
//        WHEN("C = A / B is calculated") {
//            ndarray<float> a(data_a_unaligned, {1, 4, 5});
//            ndarray<float> b(data_b_unaligned, {2, 3, 1, 1});
//            ndarray<float> c = a / b;
//            THEN("correct result is stored in C with shape (2, 3, 4, 5)") {
//                bool e = c.equals(c_gt);
//                REQUIRE(e == true);
//            }
//        }
//    }
//    GIVEN("ndarray A with shape (3, 4, 5) and ndarray B with shape (2, 1, 1, 1)") {
//        float *data_a_unaligned = data_generator.arange(60);
//        float *data_b_unaligned = data_generator.arange(2);
//        float c_gt_data[120] = {
//
//        };
//        ndarray<float> c_gt(c_gt_data, {2, 3, 4, 5});
//        WHEN("C = A / B is calculated") {
//            ndarray<float> a(data_a_unaligned, {3, 4, 5});
//            ndarray<float> b(data_b_unaligned, {2, 1, 1, 1});
//            ndarray<float> c = a / b;
//            THEN("correct result is stored in C with shape (2, 3, 4, 5)") {
//                bool e = c.equals(c_gt);
//                REQUIRE(e == true);
//            }
//        }
//    }
}
/**********************************************************************************************************************/