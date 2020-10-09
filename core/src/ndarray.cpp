#include <functional>
#include <numeric>
#include <sstream>
#include <string>

#include "../include/ndarray.hpp"
#include "../include/utils.hpp"

using namespace std;


void M_ASSERT(const char* expr_str, bool expr, const char* file, int line, const char* msg) {
    if (!expr) {
        std::cerr << "Assert failed:\t" << msg << "\n"
                  << "Expected:\t" << expr_str << "\n"
                  << "Source:\t\t" << file << ", line " << line << "\n";
        abort();
    }
}

void ASSERT_INDICES_IN_RANGE(const std::vector<unsigned> &shape, const std::vector<unsigned> indices) {
    for(unsigned i = 0; i < indices.size(); i++) {
        std::ostringstream message;
        message << "Index " << indices[i] << " not in range " << "(0, " << shape[i] - 1 << ")";

        ASSERT_CONDITION(indices[i] >= 0 && indices[i] <= shape[i] - 1, message.str().c_str());
    }
}

template <typename T>
ndarray<T>::ndarray(const std::vector<unsigned> &shape)
    : shape(shape)
{
    ASSERT_CONDITION(!shape.empty(),
    "shape is not allowed to be empty");

    const unsigned shape_product = accumulate(shape.begin(), shape.end(), 1, multiplies<unsigned>());
    this->size = shape_product;
    this->dim = shape.size();
    this->data = new T[shape_product];

    if(this->dim > 1) {
        vector<unsigned> subps;
        for(int i = 1; i < this->dim; i++) {
            unsigned sp = accumulate(shape.begin() + i, shape.end(), 1, multiplies<unsigned>());
            subps.push_back(sp);
        }
       this->shape_products = subps;
    } 
    else
        this->shape_products = {shape[0]};
}

template <typename T>
ndarray<T>::ndarray(T *data, const std::vector<unsigned> &shape)
    : shape(shape), data(data)
{
    ASSERT_CONDITION(!shape.empty(),
    "shape is not allowed to be empty");

    const unsigned shape_product = accumulate(shape.begin(), shape.end(), 1, multiplies<unsigned>());
    this->size = shape_product;
    this->dim = shape.size();

    if(this->dim > 1) {
        vector<unsigned> subps;
        for(int i = 1; i < this->dim; i++) {
            unsigned sp = std::accumulate(shape.begin() + i, shape.end(), 1, std::multiplies<unsigned>());
            subps.push_back(sp);
        }
        this->shape_products = subps;
    }
    else
        this->shape_products = {shape[0]};
}

template <typename T>
void ndarray<T>::reshape(const std::vector<unsigned> &new_shape) {
    unsigned p = std::accumulate(new_shape.begin(), new_shape.end(), 1, std::multiplies<unsigned>());

    ASSERT_CONDITION(this->size == p,
    "When reshaping, new shape product must be equal to target ndarray size");

    this->shape = new_shape;
    this->dim = new_shape.size();
    if(new_shape.size() > 1) {
        vector<unsigned> subps;
        for(int i = 1; i < new_shape.size(); i++) {
            unsigned sp = std::accumulate(new_shape.begin() + i, new_shape.end(), 1, std::multiplies<unsigned>());
            subps.push_back(sp);
        }
        this->shape_products = subps;
    }
    else
        this->shape_products = {new_shape[0]};
}

template <typename T>
ndarray<T> ndarray<T>::at(const std::vector<unsigned> &indices) const {
    const unsigned indices_size = indices.size();
    const unsigned shape_size = this->shape.size();

    ASSERT_CONDITION(indices_size >= 1 && indices_size <= this->dim - 1,
    "Number of indices must be between 1 and dim-1");
    ASSERT_INDICES_IN_RANGE(this->shape, indices);

    if(this->dim == 2) {
        return ndarray<T>(this->data + (indices[0] * this->shape[1]), {this->shape[1]});
    }

    unsigned index = 0;
    for(unsigned i = 0; i < indices.size(); i++) {
        index += indices[i] * this->shape_products[i];
    }

    vector<unsigned> new_shape;
    for(unsigned i = indices_size; i < shape_size; i++) {
        new_shape.push_back(this->shape[i]);
    }

    T *start = this->data + index;
    return ndarray<T>(start, new_shape);
}


template <typename T>
ndarray<T> ndarray<T>::copy_at(const std::vector<unsigned> &indices) const {
    const unsigned indices_size = indices.size();
    const unsigned shape_size = this->shape.size();

    ASSERT_CONDITION(indices_size >= 1 && indices_size <= this->dim - 1,
    "Number of indices must be between 1 and dim-1");
    ASSERT_INDICES_IN_RANGE(this->shape, indices);

    unsigned index = 0;
    for(unsigned i = 0; i < indices.size(); i++) {
        index += indices[i] * this->shape_products[i];
    }

    vector<unsigned> new_shape;
    for(unsigned i = indices_size; i < shape_size; i++) {
        new_shape.push_back(this->shape[i]);
    }
    const unsigned new_shape_product =
            accumulate(new_shape.begin(), new_shape.end(), 1, multiplies<unsigned>());

    T *start = this->data + index;
    T *end = start + new_shape_product;
    T *slice = new T[new_shape_product];
    std::copy(start, end, slice);

    return ndarray<T>(slice, new_shape);
}

template<typename T>
template<typename... A>
T ndarray<T>::operator()(A... indices) const {
    vector<unsigned> is = {(unsigned)indices...};
    unsigned indices_size = is.size();
    unsigned index = is[0];

    ASSERT_CONDITION(indices_size == this->shape.size(),
    "Index access requires same number of indices as shape size, use view for sub-arrays");
    ASSERT_INDICES_IN_RANGE(this->shape, is);

    if(indices_size == 1)
        return this->data[index];

    index = (this->shape[1] * is[0]) + is[1];

    if(indices_size == 2)
        return this->data[index];

    for(int i = 2; i < indices_size; i++) {
        index = index * this->shape[i] + is[i];
    }

    return this->data[index];
}

template<typename T>
template<typename... A>
T& ndarray<T>::operator()(A... indices) {
    vector<unsigned> is = {(unsigned)indices...};
    unsigned indices_size = is.size();
    unsigned index = is[0];

    ASSERT_CONDITION(indices_size == this->shape.size(),
    "Index access requires same number of indices as shape size, use view for sub-arrays");
    ASSERT_INDICES_IN_RANGE(this->shape, is);

    if(indices_size == 1)
        return this->data[index];

    index = (this->shape[1] * is[0]) + is[1];

    if(indices_size == 2)
        return this->data[index];

    for(int i = 2; i < indices_size; i++) {
        index = index * this->shape[i] + is[i];
    }

    return this->data[index];
}

template <typename T>
bool ndarray<T>::operator==(const ndarray<T> arh) {
    ASSERT_CONDITION(arh.size == this->size && arh.shape == this->shape,
    "Only arrays with same shape and size can be compared");

    for(unsigned i = 0; i < this->size; i++) {
        if(this->data[i] != arh.data[i]) {
            return false;
        }
    }
    
    return true;
}

template <typename T>
ndarray<T> ndarray<T>::operator+(const ndarray<T> a) const {
    ASSERT_CONDITION(a.size == this->size && a.shape == this->shape,
    "Only arrays with same shape and size can be added");

    T *s = new T[this->size];
    for(unsigned i = 0; i < a.size; i++) {
        s[i] = this->data[i] + a.data[i];
    }

    return ndarray<T>(s, this->shape);
}

template <typename T>
ndarray<T>& ndarray<T>::operator+=(const ndarray<T> &a) {
    ASSERT_CONDITION(a.size == this->size && a.shape == this->shape,
    "Only arrays with same shape and size can be added");

    for(unsigned i = 0; i < this->size; i++) {
        this->data[i] += a.data[i];
    }

    return *this;
}

template <typename T>
ndarray<T>& ndarray<T>::operator+=(const T &v) {
    for(unsigned i = 0; i < this->size; i++) {
        this->data[i] += v;
    }

    return *this;
}

template <typename T>
ndarray<T> ndarray<T>::operator-(const ndarray<T> a) const {
    ASSERT_CONDITION(a.size == this->size && a.shape == this->shape,
    "Only arrays with same shape and size can be subtracted");

    T *s = new T[this->size];
    for(unsigned i = 0; i < a.size; i++) {
        s[i] = this->data[i] - a.data[i];
    }

    return ndarray<T>(s, this->shape);
}

template <typename T>
ndarray<T>& ndarray<T>::operator-=(const ndarray<T> &a) {
    ASSERT_CONDITION(a.size == this->size && a.shape == this->shape,
    "Only arrays with same shape and size can be subtracted");

    for(unsigned i = 0; i < this->size; i++) {
        this->data[i] -= a.data[i];
    }

    return *this;
}

template <typename T>
ndarray<T>& ndarray<T>::operator-=(const T &v) {
    for(unsigned i = 0; i < this->size; i++) {
        this->data[i] -= v;
    }

    return *this;
}

template <typename T>
ndarray<T> ndarray<T>::operator*(const ndarray<T> a) const {
    ASSERT_CONDITION(a.size == this->size && a.shape == this->shape,
    "Only arrays with same shape and size can be multiplied");

    T *s = new T[this->size];
    for(unsigned i = 0; i < a.size; i++) {
        s[i] = this->data[i] * a.data[i];
    }

    return ndarray<T>(s, this->shape);
}

template <typename T>
ndarray<T>& ndarray<T>::operator*=(const ndarray<T> &a) {
    ASSERT_CONDITION(a.size == this->size && a.shape == this->shape,
    "Only arrays with same shape and size can be multiplied");

    for(unsigned i = 0; i < this->size; i++) {
        this->data[i] *= a.data[i];
    }

    return *this;
}

template <typename T>
ndarray<T>& ndarray<T>::operator*=(const T &v) {
    for(unsigned i = 0; i < this->size; i++) {
        this->data[i] *= v;
    }

    return *this;
}

template <typename T>
ndarray<T> ndarray<T>::operator/(const ndarray<T> a) const {
    ASSERT_CONDITION(a.size == this->size && a.shape == this->shape,
    "Only arrays with same shape and size can be divided");

    T *s = new T[this->size];
    for(unsigned i = 0; i < a.size; i++) {
        s[i] = this->data[i] / a.data[i];
    }
    return ndarray<T>(s, this->shape);
}

template <typename T>
ndarray<T>& ndarray<T>::operator/=(const ndarray<T> &a) {
    ASSERT_CONDITION(a.size == this->size && a.shape == this->shape,
    "Only arrays with same shape and size can be divided");

    for(unsigned i = 0; i < this->size; i++) {
        this->data[i] /= a.data[i];
    }

    return *this;
}

template <typename T>
ndarray<T>& ndarray<T>::operator/=(const T &v) {
    for(unsigned i = 0; i < this->size; i++) {
        this->data[i] /= v;
    }

    return *this;
}

template <typename T>
void ndarray<T>::generate_indices(vector<unsigned> shp, vector<unsigned> &acc, vector<vector<unsigned>> &result) const {
    /*
     * For given:
     *  - shape, [sh] (s1, s2, ... ,sN)
     *  - empty accumulator, [acc] (0_1, 0_2, ... 0_N)
     *  - empty result matrix, [result]
     *
     * this function generates result matrix [result] having P index tuples
     *      (i_11, i_12, ..., i_1N)
     *      (i_21, i_22, ..., i_2N)
     *              .
     *              .
     *              .
     *      (i_P1, i_P2, ..., i_PN)
     *
     * where P = s1 * s2 * .. * sN
     *
     * returned matrix is equivalent to sN number of nester loops
     *
     *  for(int i1 = 0; i1 < s1; i1++)
     *      for(int i2 = 0; i2 < s2; i2++)
     *          .
     *          .
     *          .
     *          for(int iN = 0; iN < sN; iN++)
     *              add((i1, i2, ..., iN)
     *
     */

    bool terminate = true;
    int d = (int)shp.size();
    for(int i = 0; i < d - 1; i++) {
        if(acc[i] != shp[i] - 1) {
            terminate = false;
            break;
        }
    }
    terminate = terminate && (acc[d - 1] == shp[d - 1]);

    if(terminate) {
        return;
    } else {
        for(int i = d - 1; i != 0; i--) {
            if(acc[i] == shp[i]) {
                acc[i] = 0;
                acc[i - 1] += 1;
            }
        }

        vector<unsigned> indices;
        indices.reserve(d);
        for(int i = 0; i < d; i++) {
            indices.push_back(acc[i]);
        }
        result.push_back(indices);
        indices.clear();

        acc[d - 1] += 1;
        generate_indices(shp, acc, result);
    }
}

template <typename T>
string print_2d(const ndarray<T> &b, unsigned lpad) {
    unsigned b_size = b.shape.size();
    unsigned n = b.shape[b_size - 2];
    unsigned m = b.shape[b_size - 1];

    ostringstream out;
    string sp_out = string(lpad, ' ');
    string sp_in = string(lpad + 1, ' ');
    string lpad_out = lpad == 0 ? "" : sp_out;
    string lpad_in = lpad == 0 ? " " : sp_in;

    out << lpad_out << "[\n";
    for(unsigned i = 0; i < n; i++) {
        out << lpad_in << "[";
        string sep2 = i == n - 1 ? "]" : "], ";
        for(unsigned j = 0; j < m; j++) {
            string sep1 = j == m - 1 ? "" : ", ";
            out << b(i, j) << sep1;
        }
        out << sep2;
        out << endl;
    }
    out << lpad_out << "]";

    string out_str = out.str();
    return out_str;
}

template <typename T>
ostream& operator<<(ostream &os, const ndarray<T> &b) {
    unsigned dim = b.dim;
    vector<unsigned> shape = b.shape;

    if(dim == 1) {
        string sep;

        os << "[";
        for(unsigned i = 0; i < b.size; i++) {
            sep = i == b.size - 1 ? "" : ", ";
            os << b.data[i] << sep;
        }
        os << "]";
    } else if(dim == 2) {
        os << print_2d(b);
    } else if (dim == 3) {
        os << "[\n";
        for(unsigned i = 0; i < shape[0]; i++) {
            ndarray<T> curr_b = b.at({i});
            os << print_2d(curr_b, 1) << endl;
        }
        os << "]";
    } else {
        vector<unsigned> new_shape;
        new_shape.reserve(dim - 2);
        for(unsigned i = 0; i < dim - 2; i++) {
            new_shape.push_back(shape[i]);
        }

        vector<vector<unsigned>> all_matrix_indices;
        vector<unsigned> index_acumulator(dim - 2, 0);
        b.generate_indices(new_shape, index_acumulator, all_matrix_indices);

        vector<unsigned> prev_indices;
        vector<unsigned> next_indices;
        vector<unsigned> curr_indices;
        unsigned n = all_matrix_indices.size();
        for(int i = 0; i < all_matrix_indices.size(); i++) {
            curr_indices = all_matrix_indices[i];
            prev_indices = i == 0 ? 
                all_matrix_indices[i] : all_matrix_indices[i - 1];
            next_indices = i != all_matrix_indices.size() - 1 ?
                all_matrix_indices[i + 1] : all_matrix_indices[i];

            ndarray<T> curr_b = b.at({curr_indices});

            open_brackets(os, i, curr_indices, prev_indices, next_indices);
            os << print_2d(curr_b, dim - 2) << endl;
            close_brackets(os, i, n, shape, curr_indices, prev_indices, next_indices);
        }
    }
    os << endl;

    string sep;
    os << "dim=" << b.dim << " shape=[";
    for(int i = 0; i < dim; i++) {
        sep = i == dim - 1 ? "" : ", ";
        os << shape[i] << sep;
    }
    os << "]";

    os << " shape_products=[";
    for(int i = 0; i < b.shape_products.size(); i++) {
        sep = i == b.shape_products.size() - 1 ? "" : ", ";
        os << b.shape_products[i] << sep;
    }
    os << "]";

    return os;
}


/* template declarations */
template class ndarray<float>;

template ostream& operator<< <float>(ostream&, const ndarray<float>&);

template float& ndarray<float>::operator()<int>(int);
template float& ndarray<float>::operator()<int, int>(int, int);
template float& ndarray<float>::operator()<int, int, int>(int, int, int);
template float& ndarray<float>::operator()<int, int, int, int>(int, int, int, int);

template float& ndarray<float>::operator()<unsigned int, unsigned int>(unsigned int, unsigned int);
/* End template declarations  */

