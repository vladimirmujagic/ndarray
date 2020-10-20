#include <iostream>

#include "../../../core/include/ndarray.hpp"

using namespace std;

#define randf(x) static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / x))


int main(int argc, char **argv) {
    float data_a[120] = {0};
    for(unsigned i = 0; i < 120; i++) {
        data_a[i] = float(i);
    }
    float data_b[5] = {0};
    for(unsigned i = 0; i < 5; i++) {
        data_b[i] = float(i);
    }

    ndarray<float> a(data_a, {2, 3, 4, 5});
    ndarray<float> b(data_b, {5});
    ndarray<float> c = a + b;

    cout << a << endl;
    cout << b << endl;
    cout << c << endl;
}

//float data_a[60] = {0};
//for(unsigned i = 0; i < 60; i++) {
//data_a[i] = float(i);
//}
//float data_b[2] = {0};
//for(unsigned i = 0; i < 2; i++) {
//data_b[i] = float(i);
//}
//
//ndarray<float> a(data_a, {3, 4, 5});
//ndarray<float> b(data_b, {2, 1, 1, 1});
//ndarray<float> c = a + b;
//
//cout << a << endl;
//cout << b << endl;
//cout << c << endl;
//
//

//
//float data_a[120] = {0};
//for(unsigned i = 0; i < 120; i++) {
//data_a[i] = float(i);
//}
//float data_b[5] = {0};
//for(unsigned i = 0; i < 5; i++) {
//data_b[i] = float(i);
//}
//
//ndarray<float> a(data_a, {2, 3, 4, 5});
//ndarray<float> b(data_b, {5});
//ndarray<float> c = a + b;
//
//cout << a << endl;
//cout << b << endl;
//cout << c << endl;


//float data_a[20] = {0};
//for(unsigned i = 0; i < 20; i++) {
//data_a[i] = float(i);
//}
//float data_b[120] = {0};
//for(unsigned i = 0; i < 120; i++) {
//data_b[i] = float(i);
//}
//
//ndarray<float> a(data_a, {4, 5});
//ndarray<float> b(data_b, {2, 3, 4, 5});
//ndarray<float> c = a + b;
//
//cout << a << endl;
//cout << b << endl;
//cout << c << endl;


//
//float data_a[20] = {0};
//for(unsigned i = 0; i < 20; i++) {
//data_a[i] = float(i);
//}
//float data_b[6] = {0};
//for(unsigned i = 0; i < 6; i++) {
//data_b[i] = float(i);
//}
//
//ndarray<float> a(data_a, {1, 4, 5});
//ndarray<float> b(data_b, {2, 3, 1, 1});
//ndarray<float> c = a + b;
//
//cout << a << endl;
//cout << b << endl;
//cout << c << endl;