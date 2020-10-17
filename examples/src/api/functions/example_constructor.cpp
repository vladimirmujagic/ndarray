#include <iostream>

#include "../../../../core/include/ndarray.hpp"
#include "../../../../tests/include/data_generator.hpp"


using namespace std;


int main() {
    DataGenerator dg;
    float *data = dg.arange(120);

    cout << "Create 1d array" << endl;
    ndarray<float> a1(data, {120});
    cout << a1 << endl << endl;

    cout << "Create 2d array" << endl;
    ndarray<float> a2(data, {6, 20});
    cout << a2 << endl << endl;

    cout << "Create 3d array" << endl;
    ndarray<float> a3(data, {3, 2, 20});
    cout << a3 << endl << endl;

    cout << "Create 4d array" << endl;
    ndarray<float> a4(data, {3, 2, 4, 5});
    cout << a4 << endl << endl;

    cout << "Create 5d array" << endl;
    ndarray<float> a5(data, {3, 2, 2, 2, 5});
    cout << a5 << endl << endl;
}