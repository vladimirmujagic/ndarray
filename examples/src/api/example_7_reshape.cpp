#include <iostream>

#include "../../../core/include/ndarray.hpp"
#include "../../../tests/include/data_generator.hpp"


using namespace std;


int main() {
    DataGenerator dg;
    float *data = dg.arange(20);

    ndarray<float> a(data, {5, 2, 2});
    a.print();

    a.reshape({2, 2, 5});
    a.print();

    a.reshape({10, 2});
    a.print();

    a.reshape({20});
    a.print();
}