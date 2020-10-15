#include <iostream>

#include "../../core/include/ndarray.hpp"

#define randf(x) static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / x))

float * random_data(unsigned size, unsigned rand_max){
    float *data = new float[size];
    for(unsigned i = 0; i < size; i++) {
        data[i] = randf(rand_max);
    }

    return data;
}

using namespace std;


int main(int argc, char **argv) {
    float *data = random_data(120, 1);

    cout << "Create ndarray" << endl;
    ndarray<float> a(data, {6, 2, 10});
    cout << a << endl << endl;

    cout << "Get subarray at index 0" << endl;
    ndarray<float> a_sub_0 = a.subarray_at({0});
    cout << a_sub_0 << endl << endl;

    cout << "Get subarray at index 3" << endl;
    ndarray<float> a_sub_3 = a.subarray_at({3});
    cout << a_sub_3 << endl << endl;

    cout << "Get subarray at index (4, 1)" << endl;
    ndarray<float> a_sub_4_1 = a.subarray_at({4, 1});
    cout << a_sub_4_1 << endl << endl;

    // Fails with assertion failed
    // ndarray<float> a_sub_4_1_0 = a.at({4, 1, 0});
}
