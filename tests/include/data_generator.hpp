#pragma once

#include <iostream>
#include <vector>

#define RANDF(x) static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / x))

template <typename T>
class DataGenerator {
public:
    DataGenerator() {}

    T* arange(unsigned v) const {
        T *data = new T[v];
        for(unsigned i = 0; i < v; i++) {
            data[i] = i;
        }

        return data;
    }

    T* like(unsigned size, T v) const {
        T *data = new T[size];
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
