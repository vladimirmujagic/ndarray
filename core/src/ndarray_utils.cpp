#include <iostream>
#include <string>

#include "../include/ndarray_utils.hpp"

using namespace std;


void open_brackets(
    ostream &os,
    const unsigned i,
    const vector<unsigned> &curr_indices,
    const vector<unsigned> &prev_indices,
    const vector<unsigned> &next_indices
) {
    string padding;

    for(int j = 0; j < curr_indices.size(); j++) {
        if(i == 0) {
            padding = string(j, ' ');
            os << padding << "[\n";
        } else {
            if(curr_indices[j] == 0 && j == curr_indices.size() - 1) {
                padding = std::string(j, ' ');
                os << padding << "[\n";
            }

            if(j > 0 && j != curr_indices.size() - 1) {
                if(curr_indices[j - 1] != prev_indices[j - 1] &&
                   curr_indices[j - 1] == next_indices[j - 1]) {
                    padding = std::string(j, ' ');
                    os << padding << "[\n";
                }
            }
        }
    }
}

void close_brackets(
    std::ostream &os,
    unsigned i,
    unsigned n,
    const vector<unsigned> &shape,
    const vector<unsigned> &curr_indices,
    const vector<unsigned> &prev_indices,
    const vector<unsigned> &next_indices
) {
    string padding;

    for(int j = (int)curr_indices.size() - 1; j >= 0; j--) {
        if(i == n - 1) {
            padding = std::string(j, ' ');
            os << padding << "]\n";
        } else {
            if(curr_indices[j] == shape[j] - 1 && j == curr_indices.size() - 1) {
                padding = std::string(j, ' ');
                os << padding << "]\n";
            }
            if(j > 0 && j != curr_indices.size() - 1) {
                if(curr_indices[j - 1] == prev_indices[j - 1] &&
                   curr_indices[j - 1] != next_indices[j - 1]) {
                    padding = std::string(j, ' ');
                    os << padding << "]\n";
                }
            }
        }
    }
}

void print_vector(const std::vector<unsigned> &v) {
    cout << "[";
    for(unsigned i = 0; i < v.size(); i++) {
        if(i == v.size() - 1)
            cout << v[i];
        else
            cout << v[i] << ", ";
    }
    cout << "]";
}
