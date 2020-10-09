#include <iostream>

#include "../../core/include/ndarray.hpp"

using namespace std;


int main(int argc, char **argv) {
    float data[20] = {0.};
    for(unsigned i = 0; i < 20; i++) { data[i] = (float)i; }

    ndarray<float> a(data, {5, 2, 2});
    cout << a << endl;

    a.reshape({2, 2, 5});
    cout << a << endl;

    a.reshape({10, 2});
    cout << a << endl;

    a.reshape({20});
    cout << a << endl;
}