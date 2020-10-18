#define CATCH_CONFIG_MAIN
#include <vector>

#include "../../../catch2/catch.hpp"

#include "../../../../core/include/ndarray.hpp"
#include "../../../include/data_generator.hpp"


using namespace std;

DataGenerator data_generator;


SCENARIO( "ndarray construction  - fill 0", "[ndarray]" ) {
    GIVEN("1d shape") {
        vector<unsigned> shape = {10};
        WHEN("1d ndarray is constructed") {
            ndarray<float> a(shape);
            THEN("data is set to 0, dimension, size, shape and strides are calculated") {
                REQUIRE(a.dim == 1);
                REQUIRE(a.size == 10);
                REQUIRE(a.shape == vector<unsigned>{10});
                REQUIRE(a.strides() == vector<unsigned>{1});
                REQUIRE(
                    vector<float>(a.data(), a.data() + a.size) ==
                    vector<float>(a.size, 0)
                );
            }
        }
    }

    GIVEN("2d shape") {
        vector<unsigned> shape = {5, 5};
        WHEN("2d ndarray is constructed") {
            ndarray<float> a(shape);
            THEN("data is set to 0, dimension, size shape and strides are calculated") {
                REQUIRE(a.dim == 2);
                REQUIRE(a.size == 25);
                REQUIRE(a.shape == vector<unsigned>{5, 5});
                REQUIRE(a.strides() == vector<unsigned>{5});
                REQUIRE(
                    vector<float>(a.data(), a.data() + a.size) ==
                    vector<float>(a.size, 0)
                );
            }
        }
    }

    GIVEN("3d shape") {
        vector<unsigned> shape = {2, 5, 5};
        WHEN("3d ndarray is constructed") {
            ndarray<float> a(shape);
            THEN("data is set to 0, dimension, size and strides are calculated") {
                REQUIRE(a.dim == 3);
                REQUIRE(a.size == 50);
                REQUIRE(a.shape == vector<unsigned>{2, 5, 5});
                REQUIRE(a.strides() == vector<unsigned>{25, 5});
                REQUIRE(
                    vector<float>(a.data(), a.data() + a.size) ==
                    vector<float>(a.size, 0)
                );
            }
        }
    }

    GIVEN("4d shape") {
        vector<unsigned> shape = {2, 2, 5, 5};
        WHEN("2d ndarray is constructed") {
            ndarray<float> a(shape);
            THEN("data is set to 0, dimension, size and strides are calculated") {
                REQUIRE(a.dim == 4);
                REQUIRE(a.size == 100);
                REQUIRE(a.shape == vector<unsigned>{2, 2, 5, 5});
                REQUIRE(a.strides() == vector<unsigned>{50, 25, 5});
                REQUIRE(
                    vector<float>(a.data(), a.data() + a.size) ==
                    vector<float>(a.size, 0)
                );
            }
        }
    }
}


SCENARIO( "ndarray construction - fill with value", "[ndarray]" ) {
    GIVEN("1d shape and value 1") {
        vector<unsigned> shape = {10};
        float v = 1.;
        WHEN("1d ndarray is constructed") {
            ndarray<float> a(v, shape);
            THEN("data is set to 0, dimension, size, shape and strides are calculated") {
                REQUIRE(a.dim == 1);
                REQUIRE(a.size == 10);
                REQUIRE(a.shape == vector<unsigned>{10});
                REQUIRE(a.strides() == vector<unsigned>{1});
                REQUIRE(
                    vector<float>(a.data(), a.data() + a.size) ==
                    vector<float>(a.size, v)
                );
            }
        }
    }

    GIVEN("2d shape and value 2") {
        vector<unsigned> shape = {5, 5};
        float v = 2.;
        WHEN("2d ndarray is constructed") {
            ndarray<float> a(v, shape);
            THEN("data is set to 0, dimension, size and strides are calculated") {
                REQUIRE(a.dim == 2);
                REQUIRE(a.size == 25);
                REQUIRE(a.shape == vector<unsigned>{5, 5});
                REQUIRE(a.strides() == vector<unsigned>{5});
                REQUIRE(
                    vector<float>(a.data(), a.data() + a.size) ==
                    vector<float>(a.size, v)
                );
            }
        }
    }

    GIVEN("3d shape and value 3") {
        vector<unsigned> shape = {2, 5, 5};
        float v = 3.;
        WHEN("3d ndarray is constructed") {
            ndarray<float> a(v, shape);
            THEN("data is set to 0, dimension, size and strides are calculated") {
                REQUIRE(a.dim == 3);
                REQUIRE(a.size == 50);
                REQUIRE(a.shape == vector<unsigned>{2, 5, 5});
                REQUIRE(a.strides() == vector<unsigned>{25, 5});
                REQUIRE(
                    vector<float>(a.data(), a.data() + a.size) ==
                    vector<float>(a.size, v)
                );
            }
        }
    }

    GIVEN("4d shape and value 4") {
        vector<unsigned> shape = {2, 2, 5, 5};
        float v = 4.;
        WHEN("2d ndarray is constructed") {
            ndarray<float> a(v, shape);
            THEN("data is set to 0, dimension, size and strides are calculated") {
                REQUIRE(a.dim == 4);
                REQUIRE(a.size == 100);
                REQUIRE(a.shape == vector<unsigned>{2, 2, 5, 5});
                REQUIRE(a.strides() == vector<unsigned>{50, 25, 5});
                REQUIRE(
                    vector<float>(a.data(), a.data() + a.size) ==
                    vector<float>(a.size, v)
                );
            }
        }
    }
}


SCENARIO( "ndarray construction with existing data", "[ndarray]" ) {
    GIVEN( "1d data stored as 1d array and its shape" ) {
        float *data = data_generator.arange(5);
        vector<unsigned> shape = {5};
        WHEN("ndarray is constructed") {
            ndarray<float> a(data, shape);
            THEN("data is assigned, dimension, size, strides are calculated") {
                REQUIRE(a.dim == 1);
                REQUIRE(a.size == 5);
                REQUIRE(a.shape == vector<unsigned>{5});
                REQUIRE(a.strides() == vector<unsigned>{1});
                REQUIRE(
                    vector<float>(a.data(), a.data() + a.size) ==
                    vector<float>{0., 1., 2., 3., 4.}
                );
            }
        }
    }

    GIVEN( "2d data stored as 1d array and its shape" ) {
        float *data = data_generator.arange(6);
        vector<unsigned> shape = {3, 2};
        WHEN("ndarray is constructed") {
            ndarray<float> a(data, shape);
            THEN("data is assigned, dimension, size, strides are calculated") {
                REQUIRE(a.dim == 2);
                REQUIRE(a.size == 6);
                REQUIRE(a.shape == vector<unsigned>{3, 2});
                REQUIRE(a.strides() == vector<unsigned>{2});
                REQUIRE(
                    vector<float>(a.data(), a.data() + a.size) ==
                    vector<float>{0., 1., 2., 3., 4., 5.}
                );
            }
        }
    }

    GIVEN( "3d data stored as 1d array and its shape" ) {
        float *data = data_generator.arange(12);
        vector<unsigned> shape = {3, 2, 2};
        WHEN("ndarray is constructed") {
            ndarray<float> a(data, shape);
            THEN("data is assigned, dimension, size, strides are calculated") {
                REQUIRE(a.dim == 3);
                REQUIRE(a.size == 12);
                REQUIRE(a.shape == vector<unsigned>{3, 2, 2});
                REQUIRE(a.strides() == vector<unsigned>{4, 2});
                REQUIRE(
                    vector<float>(a.data(), a.data() + a.size) ==
                    vector<float>{0., 1., 2., 3., 4., 5., 6., 7., 8., 9., 10., 11.}
                );
            }
        }
    }

    GIVEN( "4d data stored as 1d array and its shape" ) {
        float *data = data_generator.arange(16);
        vector<unsigned> shape = {2, 2, 2, 2};
        WHEN("ndarray is constructed") {
            ndarray<float> a(data, shape);
            THEN("data is assigned, dimension, size, strides are calculated") {
                REQUIRE(a.dim == 4);
                REQUIRE(a.size == 16);
                REQUIRE(a.shape == vector<unsigned>{2, 2, 2, 2});
                REQUIRE(a.strides() == vector<unsigned>{8, 4, 2});
                REQUIRE(
                    vector<float>(a.data(), a.data() + a.size) ==
                    vector<float>{0., 1., 2., 3., 4., 5., 6., 7., 8., 9., 10., 11., 12., 13., 14., 15.}
                );
            }
        }
    }
}
