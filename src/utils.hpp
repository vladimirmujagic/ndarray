#pragma once

#include <iostream>
#include <vector>


void open_brackets(
    std::ostream &os,
    unsigned i,
    const std::vector<unsigned> &curr_indices,
    const std::vector<unsigned> &prev_indices,
    const std::vector<unsigned> &next_indices
);

void close_brackets(
    std::ostream &os,
    unsigned i,
    unsigned n,
    const std::vector<unsigned> &shape,
    const std::vector<unsigned> &curr_indices,
    const std::vector<unsigned> &prev_indices,
    const std::vector<unsigned> &next_indices
);

