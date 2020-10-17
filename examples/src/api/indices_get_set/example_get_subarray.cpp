#include <iostream>


#include "../../../../core/include/ndarray.hpp"
#include "../../../../tests/include/data_generator.hpp"


using namespace std;


int main() {
    DataGenerator dg;
    float *data = dg.arange(120);

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