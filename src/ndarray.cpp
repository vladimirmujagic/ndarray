#include <functional>
#include <numeric>
#include <sstream>
#include <string>

#include "ndarray.hpp"
#include "utils.hpp"

using namespace std;


void __M_Assert(const char* expr_str, bool expr, const char* file, int line, const char* msg) {
    if (!expr) {
        std::cerr << "Assert failed:\t" << msg << "\n"
                  << "Expected:\t" << expr_str << "\n"
                  << "Source:\t\t" << file << ", line " << line << "\n";
        abort();
    }
}

template <typename T>
ndarray<T>::ndarray(const std::vector<unsigned> &shape)
    : shape(shape)
{
    M_Assert(!shape.empty(),
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
    M_Assert(!shape.empty(),
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

template<typename T>
template<typename... A>
T ndarray<T>::operator()(A... indices) const {
    vector<unsigned> is = {(unsigned)indices...};
    unsigned indices_size = is.size();
    unsigned index = is[0];

    M_Assert(indices_size == this->shape.size(),
    "Index access requires same number of indices as shape size, use view for sub-arrays");

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

    M_Assert(indices_size == this->shape.size(),
    "Index access requires same number of indices as shape size, use view for sub-arrays");

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
ndarray<T> ndarray<T>::view(const std::vector<unsigned> &indices) const {
    const unsigned indices_size = indices.size();
    const unsigned shape_size = this->shape.size();

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
ndarray<T> ndarray<T>::copy(const std::vector<unsigned> &indices) const {
    const unsigned indices_size = indices.size();
    const unsigned shape_size = this->shape.size();

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

template <typename T>
bool ndarray<T>::operator==(const ndarray<T> arh) {
    for(unsigned i = 0; i < this->size; i++) {
        if(this->data[i] != arh.data[i]) {
            return false;
        }
    }
    
    return true;
}

template <typename T>
ndarray<T> ndarray<T>::operator+(const ndarray<T> a) const {
    T *s = new T[this->size];
    for(unsigned i = 0; i < a.size; i++) {
        s[i] = this->data[i] + a.data[i];
    }

    return ndarray<T>(s, this->shape);
}

template <typename T>
ndarray<T>& ndarray<T>::operator+=(const ndarray<T> &a) {
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
    T *s = new T[this->size];
    for(unsigned i = 0; i < a.size; i++) {
        s[i] = this->data[i] - a.data[i];
    }

    return ndarray<T>(s, this->shape);
}

template <typename T>
ndarray<T>& ndarray<T>::operator-=(const ndarray<T> &a) {
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
    T *s = new T[this->size];
    for(unsigned i = 0; i < a.size; i++) {
        s[i] = this->data[i] * a.data[i];
    }

    return ndarray<T>(s, this->shape);
}

template <typename T>
ndarray<T>& ndarray<T>::operator*=(const ndarray<T> &a) {
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
    T *s = new T[this->size];
    for(unsigned i = 0; i < a.size; i++) {
        s[i] = this->data[i] / a.data[i];
    }
    return ndarray<T>(s, this->shape);
}

template <typename T>
ndarray<T>& ndarray<T>::operator/=(const ndarray<T> &a) {
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
void ndarray<T>::generate_indices(
    vector<unsigned> shape,
    vector<unsigned> &acc,
    vector<vector<unsigned>> &result
) const {
    bool terminate = true;
    int dim = (int)shape.size();
    for(int i = 0; i < dim - 1; i++) {
        if(acc[i] != shape[i] - 1) {
            terminate = false;
            break;
        }
    }
    terminate = terminate && (acc[dim - 1] == shape[dim - 1]);

    if(terminate) {
        return;
    } else {
        for(int i = dim - 1; i != 0; i--) {
            if(acc[i] == shape[i]) {
                acc[i] = 0;
                acc[i - 1] += 1;
            }
        }

        vector<unsigned> indices;
        indices.reserve(dim);
        for(int i = 0; i < dim; i++) {
            indices.push_back(acc[i]);
        }
        result.push_back(indices);
        indices.clear();

        acc[dim - 1] += 1;
        generate_indices(shape, acc, result);
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
            ndarray<T> curr_b = b.view({i});
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

            ndarray<T> curr_b = b.view({curr_indices});

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

