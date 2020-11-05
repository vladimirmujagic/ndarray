#include <iostream>

#include "../../../core/include/ndarray.hpp"
#include "../../../tests/include/data_generator.hpp"


using namespace std;


int main() {
    DataGenerator dg;
    float *data_a = dg.arange(120);
    float *data_b = dg.arange(20);

    ndarray<float> a(data_a, {2, 3, 4, 5});
    ndarray<float> b(data_b, {4, 5});
    a.print();
    b.print();

    a += b;

    a.print();
    b.print();

}