#include <vector>

#include "ndarray_validation.hpp"

using namespace std;


vector<unsigned> _next_cartesian_tuple(vector<unsigned> acc, vector<unsigned> sets) {
    bool terminate = true;
    int d = (int)sets.size();
    for(int i = 0; i < d - 1; i++) {
        if(acc[i] != sets[i] - 1) {
            terminate = false;
            break;
        }
    }

    if(terminate && acc[d-1] == sets[d-1] - 1)
        throw StopIteration();

    acc[d - 1] += 1;

    for(int i = d - 1; i != 0; i--) {
        if(acc[i] == sets[i]) {
            acc[i] = 0;
            acc[i-1] += 1;
        }
    }

    return acc;
}

void _cartesian_product(vector<unsigned> sets, vector<unsigned> &acc, vector<vector<unsigned>> &cp) {
    bool terminate = true;
    int d = (int)sets.size();
    for(int i = 0; i < d - 1; i++) {
        if(acc[i] != sets[i] - 1) {
            terminate = false;
            break;
        }
    }
    terminate = terminate && (acc[d - 1] == sets[d - 1]);

    if(terminate) {
        return;
    } else {
        for(int i = d - 1; i != 0; i--) {
            if(acc[i] == sets[i]) {
                acc[i] = 0;
                acc[i - 1] += 1;
            }
        }

        vector<unsigned> indices;
        indices.reserve(d);
        for(int i = 0; i < d; i++) {
            indices.push_back(acc[i]);
        }
        cp.push_back(indices);
        indices.clear();

        acc[d - 1] += 1;
        _cartesian_product(sets, acc, cp);
    }
}