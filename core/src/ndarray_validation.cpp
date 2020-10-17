#include <iostream>
#include <sstream>
#include <vector>

#include "../include/ndarray_validation.hpp"

using namespace std;


void M_ASSERT(const char* expr_str, bool expr, const char* file, int line, const char* msg) {
    if (!expr) {
        std::cerr << "Assert failed:\t" << msg      << "\n"
                  << "Expected:\t"      << expr_str << "\n"
                  << "Source:\t\t"      << file     << ", line " << line << "\n";
        abort();
    }
}

void ASSERT_INDICES_IN_RANGE(const vector<unsigned> &shape, const vector<unsigned> indices) {
    for(unsigned i = 0; i < indices.size(); i++) {
        std::ostringstream message;
        message << "Index " << indices[i] << " not in range " << "(0, " << shape[i] - 1 << ")";

        ASSERT_CONDITION(indices[i] >= 0 && indices[i] <= shape[i] - 1,
                         message.str().c_str());
    }
}

void ASSERT_SHAPES_MATCH(const vector<unsigned> &shape1, const vector<unsigned> shape2) {
    vector<unsigned> smaller_shape, bigger_shape;
    if(shape1.size() > shape2.size()) {
        bigger_shape = shape1;
        smaller_shape = shape2;
    } else {
        bigger_shape = shape2;
        smaller_shape = shape1;
    }

    unsigned diff = bigger_shape.size() - smaller_shape.size();
    for(int i = 0; i < smaller_shape.size(); i++) {
        std::ostringstream message;
        message << "Shape values mismatch " << smaller_shape[i] << " != " << bigger_shape[i+diff];

        ASSERT_CONDITION(smaller_shape[i] == bigger_shape[i+diff] ||
            (smaller_shape[i] == 1 || bigger_shape[i+diff] == 1),
        message.str().c_str()
        );
    }
}