#include <iostream>


#include "../../../core/include/ndarray.hpp"
#include "../../../tests/include/data_generator.hpp"


using namespace std;


int main() {
    DataGenerator dg;
    float *data = dg.arange(120);

    cout << "Create ndarray" << endl;
    ndarray<float> a(data, {6, 2, 10});
    a.print();

    cout << "Get subarray at index 0" << endl;
    ndarray<float> a_sub_0 = a.subarray_at({0});
    a_sub_0.print();

    cout << "Get subarray at index 3" << endl;
    ndarray<float> a_sub_3 = a.subarray_at({3});
    a_sub_3.print();

    cout << "Get subarray at index (4, 1)" << endl;
    ndarray<float> a_sub_4_1 = a.subarray_at({4, 1});
    a_sub_4_1.print();

    // Fails with assertion failed
    // ndarray<float> a_sub_4_1_0 = a.at({4, 1, 0});
}