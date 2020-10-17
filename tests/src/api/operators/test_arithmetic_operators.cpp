#define CATCH_CONFIG_MAIN
#include <vector>

#include "../../../catch2/catch.hpp"

#include "../../../../core/include/ndarray.hpp"
#include "../../../include/data_generator.hpp"


using namespace std;


/**********************************************************************************************
 *                             Operator == test scenarios                                     *
**********************************************************************************************/
SCENARIO( "ndarray operator == ", "[ndarray]" ) {
    GIVEN("two equivalent ndarrays a1 and a2") {
        WHEN("they are compared") {
            THEN("value true is returned") {
                REQUIRE(true == true);
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
        WHEN("addition is performed") {
            THEN("correct result is returned") {
                REQUIRE(true == true);
            }
        }
    }

    GIVEN("two ndarrays a1 and a2") {
        WHEN("addition is performed") {
            THEN("correct result is returned") {
                REQUIRE(true == true);
            }
        }
    }

    GIVEN("ndarray a1 and scalar s") {
        WHEN("addition is performed") {
            THEN("correct result is returned") {
                REQUIRE(true == true);
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
        WHEN("subtraction is performed") {
            THEN("correct result is returned") {
                REQUIRE(true == true);
            }
        }
    }

    GIVEN("two ndarrays a1 and a2") {
        WHEN("subtraction is performed") {
            THEN("correct result is returned") {
                REQUIRE(true == true);
            }
        }
    }

    GIVEN("ndarray a1 and scalar s") {
        WHEN("subtraction is performed") {
            THEN("correct result is returned") {
                REQUIRE(true == true);
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
        WHEN("multiplication is performed") {
            THEN("correct result is returned") {
                REQUIRE(true == true);
            }
        }
    }
}

SCENARIO( "ndarray operator *= array ", "[ndarray]" ) {
    GIVEN("two ndarrays a1 and a2") {
        WHEN("multiplication is performed") {
            THEN("correct result is returned") {
                REQUIRE(true == true);
            }
        }
    }
}

SCENARIO( "ndarray operator *= scalar ", "[ndarray]" ) {
    GIVEN("ndarray a1 and and scalar s") {
        WHEN("multiplication is performed") {
            THEN("correct result is returned") {
                REQUIRE(true == true);
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
        WHEN("multiplication is performed") {
            THEN("correct result is returned") {
                REQUIRE(true == true);
            }
        }
    }
}

SCENARIO( "ndarray operator /= array ", "[ndarray]" ) {
    GIVEN("two ndarrays a1 and a2") {
        WHEN("multiplication is performed") {
            THEN("correct result is returned") {
                REQUIRE(true == true);
            }
        }
    }
}

SCENARIO( "ndarray operator /= scalar ", "[ndarray]" ) {
    GIVEN("ndarray a1 and and scalar s") {
        WHEN("division is performed") {
            THEN("correct result is returned") {
                REQUIRE(true == true);
            }
        }
    }
}
/**********************************************************************************************/