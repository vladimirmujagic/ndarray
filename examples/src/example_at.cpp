#include <iostream>

#include "../../core/include/ndarray.hpp"

using namespace std;

#define randf(x) static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / x))


int main(int argc, char **argv) {
    float data[120] = {0};
    for(unsigned i = 0; i < 120; i++) {
        data[i] = randf(20);
    }

    ndarray<float> a(data, {2, 3, 20});
    cout << a << endl;

    ndarray<float> a_sub = a.at({0});
    cout << a_sub << endl;

    a_sub.reshape({3, 2, 10});
    cout << a_sub << endl;

    ndarray<float> a_sub_sub = a_sub.at({0, 0});
    cout << a_sub_sub << endl;
    a_sub_sub.reshape({10, 1});
    cout << a_sub_sub << endl;
}