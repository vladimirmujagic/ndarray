#pragma once

#include <iostream>
#include <vector>

#define RANDF(x) static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / x))


class DataGenerator {
public:
    DataGenerator() {}

    float * arange(unsigned v) const {
        float *data = new float[v];
        for(unsigned i = 0; i < v; i++) {
            data[i] = i;
        }

        return data;
    }

    float * like(unsigned size, float v) const {
        float *data = new float[size];
        for(unsigned i = 0; i < size; i++) {
            data[i] = v;
        }

        return data;
    }

    float * random(unsigned size, unsigned rand_max) const {
        float *data = new float[size];
        for(unsigned i = 0; i < size; i++) {
            data[i] = RANDF(rand_max);
        }

        return data;
    }
};
