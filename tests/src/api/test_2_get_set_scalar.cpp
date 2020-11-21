#define CATCH_CONFIG_MAIN
#include "../../catch2/catch.hpp"

#include "../../../core/include/ndarray.hpp"
#include "../../include/data_generator.hpp"

using namespace std;


DataGenerator<float> data_generator;


SCENARIO( "ndarray get/set scalar using operator ()", "[ndarray]" ) {
    GIVEN("1d array and index (i)") {
        float *data = data_generator.arange(5);
        vector<unsigned> shape = {5};
        ndarray<float> a(data, shape);
        unsigned i = 2;

        WHEN("element is accessed") {
            float s = a(i);
            THEN("correct value is returned") {
                REQUIRE(s == 2.);
            }
        }
        WHEN("element is set") {
            a(i) = 6.;
            THEN("correct value is assigned") {
                REQUIRE(a(i) == 6.);
            }
        }
    }

    GIVEN("2d array and indices (i, j)") {
        float *data = data_generator.arange(4);
        vector<unsigned> shape = {2, 2};
        ndarray<float> a(data, shape);
        unsigned i = 1;
        unsigned j = 0;

        WHEN("element is accessed") {
            float s = a(i, j);
            THEN("correct value is returned") {
                REQUIRE(s == 2.);
            }
        }
        WHEN("element is set") {
            a(i, j) = 6.;
            THEN("correct value is assigned") {
                REQUIRE(a(i, j) == 6.);
            }
        }
    }

    GIVEN("3d array and indices (i, j, k)") {
        float *data = data_generator.arange(8);
        vector<unsigned> shape = {2, 2, 2};
        ndarray<float> a(data, shape);
        unsigned i = 1;
        unsigned j = 0;
        unsigned k = 1;

        WHEN("element is accessed") {
            float s = a(i, j, k);
            THEN("correct value is returned") {
                REQUIRE(s == 5.);
            }
        }
        WHEN("element is set") {
            a(i, j, k) = 6.;
            THEN("correct value is assigned") {
                REQUIRE(a(i, j, k) == 6.);
            }
        }
    }

    GIVEN("4d array and indices (i, j, k, l)") {
        float *data = data_generator.arange(16);
        vector<unsigned> shape = {2, 2, 2, 2};
        ndarray<float> a(data, shape);
        unsigned i = 1;
        unsigned j = 0;
        unsigned k = 1;
        unsigned l = 0;

        WHEN("element is accessed") {
            float s = a(i, j, k, l);
            THEN("correct value is returned") {
                REQUIRE(s == 10);
            }
        }
        WHEN("element is set") {
            a(i, j, k, l) = 6.;
            THEN("correct value is assigned") {
                REQUIRE(a(i, j, k, l) == 6.);
            }
        }
    }

    // ...
}


SCENARIO( "ndarray get/set scalar at() method", "[ndarray]" ) {
    GIVEN("1d array and index (i)") {
        float *data = data_generator.arange(5);
        vector<unsigned> shape = {5};
        ndarray<float> a(data, shape);
        unsigned i = 2;

        WHEN("element is accessed") {
            float s = a.at({i});
            THEN("correct value is returned") {
                REQUIRE(s == 2.);
            }
        }
        WHEN("element is set") {
            a.at({i}) = 6.;
            THEN("correct value is assigned") {
                REQUIRE(a.at({i}) == 6.);
            }
        }
    }

    GIVEN("2d array and indices (i, j)") {
        float *data = data_generator.arange(4);
        vector<unsigned> shape = {2, 2};
        ndarray<float> a(data, shape);
        unsigned i = 1;
        unsigned j = 0;

        WHEN("element is accessed") {
            float s = a.at({i, j});
            THEN("correct value is returned") {
                REQUIRE(s == 2.);
            }
        }
        WHEN("element is set") {
            a.at({i, j}) = 6.;
            THEN("correct value is assigned") {
                REQUIRE(a.at({i, j}) == 6.);
            }
        }
    }

    GIVEN("3d array and indices (i, j, k)") {
        float *data = data_generator.arange(8);
        vector<unsigned> shape = {2, 2, 2};
        ndarray<float> a(data, shape);
        unsigned i = 1;
        unsigned j = 0;
        unsigned k = 1;

        WHEN("element is accessed") {
            float s = a.at({i, j, k});
            THEN("correct value is returned") {
                REQUIRE(s == 5.);
            }
        }
        WHEN("element is set") {
            a.at({i, j, k}) = 6.;
            THEN("correct value is assigned") {
                REQUIRE(a.at({i, j, k}) == 6.);
            }
        }
    }

    GIVEN("4d array and indices (i, j, k, l)") {
        float *data = data_generator.arange(16);
        vector<unsigned> shape = {2, 2, 2, 2};
        ndarray<float> a(data, shape);
        unsigned i = 1;
        unsigned j = 0;
        unsigned k = 1;
        unsigned l = 0;

        WHEN("element is accessed") {
            float s = a.at({i, j, k, l});
            THEN("correct value is returned") {
                REQUIRE(s == 10);
            }
        }
        WHEN("element is set") {
            a.at({i, j, k, l}) = 6.;
            THEN("correct value is assigned") {
                REQUIRE(a.at({i, j, k, l}) == 6.);
            }
        }
    }

    // ...
}
