//#define CATCH_CONFIG_MAIN
//
//#include "../../catch2/catch.hpp"

#include "../../../core/include/ndarray.hpp"
#include "../../../core/include/ndarray_validation.hpp"

#include <iostream>
#include <vector>


using namespace std;


void print_vec(vector<unsigned > v) {
    for(int i = 0; i < v.size(); i++) {
        cout << v[i] << " ";
    }
    cout << endl;
}


int main() {
    ndarray<float> a(1., {2, 2});
    vector<unsigned> shape = {2, 4, 2, 3};
    vector<unsigned> curr_tuple = {0, 0, 0, 0};
    print_vec(curr_tuple);
    while(true) {
        try {
            curr_tuple = a._next_cartesian_tuple(curr_tuple, shape);
            print_vec(curr_tuple);
        } catch (StopIteration& e) {
            cerr << e.what() << endl;
            break;
        }
    }

    cout << endl;

    vector<vector<unsigned>> result;
    vector<unsigned> acc = {0, 0, 0, 0};
    a._cartesian_product(shape, acc, result);
    for(unsigned i = 0; i < result.size(); i++) {
        print_vec(result[i]);
    }
}