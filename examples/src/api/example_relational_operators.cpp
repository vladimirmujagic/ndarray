#include <iostream>

#include "../../../core/include/ndarray.hpp"

using namespace std;

#define randf(x) static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / x))


int main(int argc, char **argv) {
    float data[120] = {0};
    for(unsigned i = 0; i < 120; i++) {
        data[i] = randf(20);
    }

}