#include <vector>


class TestData {
public:
    float *a1d_data, *a2d_data, *a3d_data, *a4d_data;
    std::vector<unsigned> a1d_shape, a2d_shape, a3d_shape, a4d_shape;

public:
    TestData() {
        this->a1d_data = new float[3];
        this->a1d_shape = {3};
        for(unsigned i = 0; i < 3; i++) { this->a1d_data[i] = (float)i; }

        this->a2d_data = new float[4 * 4];
        this->a2d_shape = {4, 4};
        for(unsigned i = 0; i < 16; i++) { this->a2d_data[i] = (float)i; }

        this->a3d_data = new float[3 * 2 * 5];
        this->a3d_shape = {3, 2, 5};
        for(unsigned i = 0; i < 30; i++) { this->a3d_data[i] = (float)i; }

        this->a4d_data = new float[4 * 3 * 2 * 5];
        this->a4d_shape = {4, 3, 2, 5};
        for(unsigned i = 0; i < 120; i++) { this->a4d_data[i] = (float)i; }
    }
};

static const TestData *test_data = new TestData();