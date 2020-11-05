#pragma once

#include <functional>
#include <algorithm>
#include <numeric>
#include <vector>

#include <iostream>
#include <sstream>

#include "ndarray_validation.hpp"
#include "ndarray_utils.hpp"

using namespace std;


enum ArithmeticOpEnum {
    ePlus = 0,
    eMinus,
    eMultiplies,
    eDiv
};

enum BitwiseOpEnum {
    eAnd = 0,
    eOr,
    eXor,
    eShiftLeft,
    eShiftRight
};

enum RelationalOpEnum {
    eEquals = 0,
    eNotEquals,
    eGt,
    eGtEquals,
    eLt,
    eLtEquals,
};


template<typename T>
class ndarray {
private:
    std::vector<unsigned> strides_;
    T* data_ = NULL;
public:
    std::vector<unsigned> shape;
    unsigned size = 0;
    unsigned dim = 0;

private:
    unsigned         _get_flat_index(const vector<unsigned> &indices) const;
public:
    /*************************************************************************
    *                             Object Lifecycle                           *
    *************************************************************************/
    ndarray();
    ndarray(const vector<unsigned> &shape);
    ndarray(const T &v, const vector<unsigned> &shape);
    ndarray(T *data, const vector<unsigned> &shape);
    ndarray(const ndarray<T> &copy);
    ~ndarray();
    ndarray<T>& operator=(const ndarray<T> &a);
    /*************************************************************************/

    /*************************************************************************
    *                             Get / Set                                  *
    *************************************************************************/
    T*               data() const;
    vector<unsigned> strides() const;
    void             _set_strides();
    /************************************************************************/

    /*************************************************************************
    *                    (i, j, k, ...) get and set                          *
    *************************************************************************/
    template<typename... I>
    T           operator()(I... indices) const;
    template<typename... I>
    T&          operator()(I... indices);
    T           at(const vector<unsigned> &indices) const;
    T&          at(const vector<unsigned> &indices);
    ndarray<T>  subarray_at(const vector<unsigned> &indices) const;
    /*************************************************************************/

    /*************************************************************************
    *                       Arithmetic operators                             *
    *************************************************************************/
    ndarray<T>  operator+(ndarray<T> &b);
    ndarray<T>& operator+=(ndarray<T> &b);
    ndarray<T>& operator+=(const T &s);
    ndarray<T>  operator-(ndarray<T> &b);
    ndarray<T>& operator-=(ndarray<T> &b);
    ndarray<T>& operator-=(const T &s);
    ndarray<T>  operator*(ndarray<T> &b);
    ndarray<T>& operator*=(ndarray<T> &b);
    ndarray<T>& operator*=(const T &s);
    ndarray<T>  operator/(ndarray<T> &b);
    ndarray<T>& operator/=(ndarray<T> &b);
    ndarray<T>& operator/=(const T &s);
    /************************************************************************/

    /*************************************************************************
    *                       Bitwise operators                                *
    *************************************************************************/
    ndarray<T>  operator&(ndarray<T> &b);
    ndarray<T>& operator&=(ndarray<T> &b);
    ndarray<T>& operator&=(const T &s);
    ndarray<T>  operator|(ndarray<T> &b);
    ndarray<T>& operator|=(ndarray<T> &b);
    ndarray<T>& operator|=(const T &s);
    ndarray<T>  operator^(ndarray<T> &b);
    ndarray<T>& operator^=(ndarray<T> &b);
    ndarray<T>& operator^=(const T &s);
    ndarray<T>  operator>>(ndarray<T> &b);
    ndarray<T>& operator>>=(ndarray<T> &b);
    ndarray<T>& operator>>=(const T &s);
    ndarray<T>  operator<<(ndarray<T> &b);
    ndarray<T>& operator<<=(ndarray<T> &b);
    ndarray<T>& operator<<=(const T &v);
    ndarray<T>& operator~();
    /************************************************************************/

    /************************************************************************
    *                      Relational operators                             *
    ************************************************************************/
    bool          equals(const ndarray<T> &a) const;
    ndarray<bool> operator==(ndarray<T> &a);
    ndarray<bool> operator==(const T &s) const;
    ndarray<bool> operator!=(ndarray<T> &a);
    ndarray<bool> operator!=(const T &s) const;
    ndarray<bool> operator>(ndarray<T> &a);
    ndarray<bool> operator>(const T &s) const;
    ndarray<bool> operator>=(ndarray<T> &a);
    ndarray<bool> operator>=(const T &s) const;
    ndarray<bool> operator<(ndarray<T> &a);
    ndarray<bool> operator<(const T &s) const;
    ndarray<bool> operator<=(ndarray<T> &a);
    ndarray<bool> operator<=(const T &s) const;
    /***********************************************************************/

    /************************************************************************
    *                      API functions                                    *
    ************************************************************************/
    void reshape(const vector<unsigned> &new_shape);
    /***********************************************************************/

    /**********************************************************************
    *                    Print related functions                         *
    **********************************************************************/
    void print();
    void open_brackets(
        ostream &os,
        const unsigned i,
        const vector<unsigned> &curr_indices,
        const vector<unsigned> &prev_indices,
        const vector<unsigned> &next_indices
    );
    string print_2d(unsigned lpad=0);
    void close_brackets(
        std::ostream &os,
        unsigned i,
        unsigned n,
        const vector<unsigned> &shape,
        const vector<unsigned> &curr_indices,
        const vector<unsigned> &prev_indices,
        const vector<unsigned> &next_indices
    );
    /***********************************************************************/
};


/***********************************************************************************************************************
 *                                               Object Lifecycle                                                      *
 **********************************************************************************************************************/
template <typename T>
ndarray<T>::ndarray() {

}

template <typename T>
ndarray<T>::~ndarray() {
    delete[] data_;
    data_ = NULL;
    dim = size = 0;
}

template <typename T>
ndarray<T>::ndarray(const ndarray<T> &copy) {
    dim = copy.dim;
    shape = copy.shape;
    strides_ = copy.strides_;
    size = copy.size;

    data_ = new T[copy.size];
    std::copy(copy.data_, copy.data_ + copy.size, data_);
}

template <typename T>
ndarray<T>& ndarray<T>::operator=(const ndarray<T> &a) {
    if(this != &a) {
        delete[] data_;

        dim = a.dim;
        shape = a.shape;
        strides_ = a.strides_;
        size = a.size;

        data_ = new T[a.size];
        std::copy(a.data_, a.data_ + a.size, data_);
    }

    return *this;
}

template <typename T>
ndarray<T>::ndarray(const vector<unsigned> &shape)
    : shape(shape)
{
    ASSERT_CONDITION(!shape.empty(),"shape is not allowed to be empty");

    const unsigned shape_product = accumulate(shape.begin(), shape.end(), 1, multiplies<unsigned>());
    size  = shape_product;
    dim   = shape.size();
    data_ = new T[shape_product];
    std::fill(data_, data_ + size, 0);

    _set_strides();
}

template <typename T>
ndarray<T>::ndarray(const T &v, const vector<unsigned> &shape)
    : shape(shape)
{
    ASSERT_CONDITION(!shape.empty(),"shape is not allowed to be empty");

    const unsigned shape_product = accumulate(shape.begin(), shape.end(), 1, multiplies<unsigned>());
    size  = shape_product;
    dim   = shape.size();
    data_ = new T[shape_product];
    std::fill(data_, data_ + size, v);

    _set_strides();
}

template <typename T>
ndarray<T>::ndarray(T *data, const vector<unsigned> &shape)
    : shape(shape)
{
    ASSERT_CONDITION(!shape.empty(),"shape is not allowed to be empty");

    const unsigned shape_product = accumulate(shape.begin(), shape.end(), 1, multiplies<unsigned>());
    size = shape_product;
    dim = shape.size();
    data_ = new T[size];
    std::copy(data, data + size,  data_);

    _set_strides();
}
/**********************************************************************************************************************/


/***********************************************************************************************************************
 *                                               Get / Set                                                             *
 **********************************************************************************************************************/
template <typename T>
T* ndarray<T>::data() const{
    return data_;
}

template <typename T>
vector<unsigned> ndarray<T>::strides() const {
    return strides_;
}
/**********************************************************************************************************************/


/***********************************************************************************************************************
 *                                           Internal utility methods                                                  *
 **********************************************************************************************************************/
template <typename T>
void ndarray<T>::_set_strides() {
    if(dim > 1) {
        vector<unsigned> subps;
        for(int i = 1; i < this->dim; i++) {
            unsigned sp = accumulate(shape.begin() + i, shape.end(), 1, multiplies<unsigned>());
            subps.push_back(sp);
        }
        strides_ = subps;
    }
    else
        strides_ = {1};
}

template <typename T>
unsigned ndarray<T>::_get_flat_index(const vector<unsigned> &indices) const {
    unsigned indices_size = indices.size();
    unsigned index = indices[0];

    ASSERT_CONDITION(indices_size == this->shape.size(),
                     "Index access requires same number of indices as shape size, use view for sub-arrays");
    ASSERT_INDICES_IN_RANGE(this->shape, indices);

    if(indices_size == 1)
        return index;

    index = (this->shape[1] * indices[0]) + indices[1];

    if(indices_size == 2)
        return index;

    for(int i = 2; i < indices_size; i++) {
        index = index * this->shape[i] + indices[i];
    }

    return index;
}
/**********************************************************************************************************************/


/***********************************************************************************************************************
 *                                         (i, j, k, ...) get and set                                                  *
 **********************************************************************************************************************/
template <typename T>
template<typename... I>
T ndarray<T>::operator()(I... indices) const {
    vector<unsigned> is = {(unsigned)indices...};
    unsigned index = _get_flat_index(is);

    return data_[index];
}

template <typename T>
template<typename... I>
T& ndarray<T>::operator()(I... indices) {
    vector<unsigned> is = {(unsigned)indices...};
    unsigned index = _get_flat_index(is);

    return data_[index];
}

template <typename T>
T ndarray<T>::at(const vector<unsigned> &indices) const {
    unsigned index = _get_flat_index(indices);

    return data_[index];
}

template <typename T>
T& ndarray<T>::at(const vector<unsigned> &indices) {
    unsigned index = this->_get_flat_index(indices);

    return data_[index];
}

template <typename T>
ndarray<T> ndarray<T>::subarray_at(const vector<unsigned> &indices) const {
    const unsigned indices_size = indices.size();
    const unsigned shape_size = this->shape.size();

    ASSERT_CONDITION(indices_size >= 1 && indices_size <= this->dim - 1,
                     "Number of indices must be between 1 and dim-1");
    ASSERT_INDICES_IN_RANGE(this->shape, indices);

    unsigned index = 0;
    for(unsigned i = 0; i < indices.size(); i++) {
        index += indices[i] * this->strides_[i];
    }

    vector<unsigned> new_shape;
    for(unsigned i = indices_size; i < shape_size; i++) {
        new_shape.push_back(this->shape[i]);
    }
    const unsigned new_shape_product =
            accumulate(new_shape.begin(), new_shape.end(), 1, multiplies<unsigned>());

    T *start = this->data_ + index;
    T *end = start + new_shape_product;
    T *slice = new T[new_shape_product];
    std::copy(start, end, slice);

    return ndarray<T>(slice, new_shape);
}
/**********************************************************************************************************************/


/***********************************************************************************************************************
 *                                             Arithmetic Operators                                                    *
 **********************************************************************************************************************/
template <typename T>
ndarray<T> ndarray<T>::operator+(ndarray<T> &b) {
    return _arithmetic_broadcast(*this, b, ePlus);
}

template <typename T>
ndarray<T>& ndarray<T>::operator+=(ndarray<T> &b) {
    *this = _arithmetic_broadcast(*this, b, ePlus);

    return *this;
}

template <typename T>
ndarray<T>& ndarray<T>::operator+=(const T &s) {
    for(unsigned i = 0; i < size; i++) {
        data_[i] += s;
    }

    return *this;
}

template <typename T>
ndarray<T> ndarray<T>::operator-(ndarray<T> &b) {
    return _arithmetic_broadcast(*this, b, eMinus);
}

template <typename T>
ndarray<T>& ndarray<T>::operator-=(ndarray<T> &b) {
    *this = _arithmetic_broadcast(*this, b, eMinus);

    return *this;
}

template <typename T>
ndarray<T>& ndarray<T>::operator-=(const T &s) {
    for(unsigned i = 0; i < size; i++) {
        data_[i] -= s;
    }

    return *this;
}

template <typename T>
ndarray<T> ndarray<T>::operator*(ndarray<T> &b) {
    return _arithmetic_broadcast(*this, b, eMultiplies);
}

template <typename T>
ndarray<T>& ndarray<T>::operator*=(ndarray<T> &b) {
    *this = _arithmetic_broadcast(*this, b, eMultiplies);

    return *this;
}

template <typename T>
ndarray<T>& ndarray<T>::operator*=(const T &s) {
    for(unsigned i = 0; i < size; i++) {
        data_[i] *= s;
    }

    return *this;
}

template <typename T>
ndarray<T>  ndarray<T>::operator/(ndarray<T> &b) {
    return _arithmetic_broadcast(*this, b, eDiv);
}

template <typename T>
ndarray<T>& ndarray<T>::operator/=(ndarray<T> &b) {
    *this = _arithmetic_broadcast(*this, b, eDiv);

    return *this;
}

template <typename T>
ndarray<T>& ndarray<T>::operator/=(const T &s) {
    for(unsigned i = 0; i < size; i++) {
        data_[i] /= s;
    }

    return *this;
}
/**********************************************************************************************************************/


/***********************************************************************************************************************
 *                                               Bitwise Operators                                                     *
 **********************************************************************************************************************/
template <typename T>
ndarray<T> ndarray<T>::operator&(ndarray<T> &b) {
    return _bitwise_broadcast(*this, b, eAnd);
}

template <typename T>
ndarray<T>& ndarray<T>::operator&=(ndarray<T> &b) {
    *this = _bitwise_broadcast(*this, b, eAnd);

    return *this;
}

template <typename T>
ndarray<T>& ndarray<T>::operator&=(const T &s) {
    for(unsigned i = 0; i < size; i++) {
        data_[i] &= s;
    }

    return *this;
}

template <typename T>
ndarray<T> ndarray<T>::operator|(ndarray<T> &b) {
    return _bitwise_broadcast(*this, b, eOr);
}

template <typename T>
ndarray<T>& ndarray<T>::operator|=(ndarray<T> &b) {
    *this = _bitwise_broadcast(*this, b, eOr);

    return *this;
}

template <typename T>
ndarray<T>& ndarray<T>::operator|=(const T &s) {
    for(unsigned i = 0; i < size; i++) {
        data_[i] |= s;
    }

    return *this;
}

template <typename T>
ndarray<T> ndarray<T>::operator^(ndarray<T> &b) {
    return _bitwise_broadcast(*this, b, eXor);
}

template <typename T>
ndarray<T>& ndarray<T>::operator^=(ndarray<T> &b) {
    *this = _bitwise_broadcast(*this, b, eXor);

    return *this;
}

template <typename T>
ndarray<T>& ndarray<T>::operator^=(const T &s) {
    for(unsigned i = 0; i < size; i++) {
        data_[i] ^= s;
    }

    return *this;
}

template <typename T>
ndarray<T> ndarray<T>::operator>>(ndarray<T> &b) {
    return _bitwise_broadcast(*this, b, eShiftRight);
}

template <typename T>
ndarray<T>& ndarray<T>::operator>>=(ndarray<T> &b) {
    *this = _bitwise_broadcast(*this, b, eShiftRight);

    return *this;
}

template <typename T>
ndarray<T>& ndarray<T>::operator>>=(const T &s) {
    for(unsigned i = 0; i < size; i++) {
        data_[i] >>= s;
    }

    return *this;
}

template <typename T>
ndarray<T> ndarray<T>::operator<<(ndarray<T> &b) {
    return _bitwise_broadcast(*this, b, eShiftLeft);
}

template <typename T>
ndarray<T>& ndarray<T>::operator<<=(ndarray<T> &b) {
    *this = _bitwise_broadcast(*this, b, eShiftLeft);

    return *this;
}

template <typename T>
ndarray<T>& ndarray<T>::operator<<=(const T &s) {
    for(unsigned i = 0; i < size; i++) {
        data_[i] <<= s;
    }

    return *this;
}

template <typename T>
ndarray<T>&  ndarray<T>::operator~() {
    for(unsigned i = 0; i < size; i++) {
        data_[i] = ~data_[i];
    }

    return *this;
}
/**********************************************************************************************************************/


/***********************************************************************************************************************
 *                                            Relational Operators                                                     *
 **********************************************************************************************************************/
template <typename T>
bool ndarray<T>::equals(const ndarray<T> &b) const {
    ASSERT_CONDITION(b.size == this->size && b.shape == this->shape,
                     "Only arrays with same shape and size can be compared");

    for(unsigned i = 0; i < size; i++) {
        if(data_[i] != b.data_[i]) {
            return false;
        }
    }

    return true;
}

template <typename T>
ndarray<bool> ndarray<T>::operator==(ndarray<T> &b){
    return _relational_broadcast(*this, b, eEquals);
}

template <typename T>
ndarray<bool> ndarray<T>::operator==(const T &s) const {
    bool *r = new bool[size];
    for(unsigned i = 0; i < size; i++) {
        r[i] = data_[i] == s;
    }

    return ndarray<bool>(r, shape);
}

template <typename T>
ndarray<bool> ndarray<T>::operator!=(ndarray<T> &b) {
    return _relational_broadcast(*this, b, eNotEquals);
}

template <typename T>
ndarray<bool> ndarray<T>::operator!=(const T &s) const {
    bool *r = new bool[size];
    for(unsigned i = 0; i < size; i++) {
        r[i] = data_[i] != s;
    }

    return ndarray<bool>(r, shape);
}

template <typename T>
ndarray<bool> ndarray<T>::operator>(ndarray<T> &b) {
    return _relational_broadcast(*this, b, eGt);
}

template <typename T>
ndarray<bool> ndarray<T>::operator>(const T &s) const {
    bool *r = new bool[size];
    for(unsigned i = 0; i < size; i++) {
        r[i] = data_[i] > s;
    }

    return ndarray<bool>(r, shape);
}

template <typename T>
ndarray<bool> ndarray<T>::operator>=(ndarray<T> &b) {
    return _relational_broadcast(*this, b, eGtEquals);
}

template <typename T>
ndarray<bool> ndarray<T>::operator>=(const T &s) const {
    bool *r = new bool[size];
    for(unsigned i = 0; i < size; i++) {
        data_[i] = data_[i] >= s;
    }

    return ndarray<bool>(r, shape);
}

template <typename T>
ndarray<bool> ndarray<T>::operator<(ndarray<T> &b) {
    return _relational_broadcast(*this, b, eLt);
}

template <typename T>
ndarray<bool> ndarray<T>::operator<(const T &s) const {
    bool *r = new bool[size];
    for(unsigned i = 0; i < size; i++) {
        data_[i] = data_[i] < s;
    }

    return ndarray<bool>(r, shape);
}

template <typename T>
ndarray<bool> ndarray<T>::operator<=(ndarray<T> &b) {
    return _relational_broadcast(*this, b, eLtEquals);
}

template <typename T>
ndarray<bool> ndarray<T>::operator<=(const T &s) const {
    bool *r = new bool[size];
    for(unsigned i = 0; i < size; i++) {
        data_[i] = data_[i] <= s;
    }

    return ndarray<bool>(r, shape);
}
/**********************************************************************************************************************/


/***********************************************************************************************************************
 *                                                 API methods                                                         *
 **********************************************************************************************************************/
template <typename T>
void ndarray<T>::reshape(const vector<unsigned> &new_shape) {
    unsigned p = accumulate(new_shape.begin(), new_shape.end(), 1, multiplies<unsigned>());

    ASSERT_CONDITION(this->size == p,
                     "When reshaping, new shape product must be equal to target ndarray size");

    this->shape = new_shape;
    this->dim = new_shape.size();
    _set_strides();
}
/**********************************************************************************************************************/


/***********************************************************************************************************************
 *                                            Print related methods                                                    *
 **********************************************************************************************************************/
template <typename T>
void ndarray<T>::print() {
    ostringstream os;

    if(dim == 1) {
        string sep;

        os << "[";
        for(unsigned i = 0; i < size; i++) {
            sep = i == size - 1 ? "" : ", ";
            os << data_[i] << sep;
        }
        os << "]";
    } else if(dim == 2) {
        os << print_2d();
    } else if (dim == 3) {
        os << "[\n";
        for(unsigned i = 0; i < shape[0]; i++) {
            ndarray<T> curr_a = this->subarray_at({i});
            os << curr_a.print_2d(1) << endl;
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
        _cartesian_product(new_shape, index_acumulator, all_matrix_indices);

        vector<unsigned> prev_indices;
        vector<unsigned> next_indices;
        vector<unsigned> curr_indices;
        unsigned n = all_matrix_indices.size();
        for(int i = 0; i < all_matrix_indices.size(); i++) {
            curr_indices = all_matrix_indices[i];
            prev_indices = i == 0 ? all_matrix_indices[i] : all_matrix_indices[i - 1];
            next_indices = i != all_matrix_indices.size() - 1 ? all_matrix_indices[i + 1] : all_matrix_indices[i];

            ndarray<T> curr_b = this->subarray_at({curr_indices});

            open_brackets(os, i, curr_indices, prev_indices, next_indices);
            os << curr_b.print_2d(dim - 2) << endl;
            close_brackets(os, i, n, shape, curr_indices, prev_indices, next_indices);
        }
    }
    os << endl;

    string sep;
    os << "dim=" << dim << " shape=[";
    for(int i = 0; i < dim; i++) {
        sep = i == dim - 1 ? "" : ", ";
        os << shape[i] << sep;
    }
    os << "]";

    os << " strides=[";
    for(int i = 0; i < strides_.size(); i++) {
        sep = i == strides_.size() - 1 ? "" : ", ";
        os << strides_[i] << sep;
    }
    os << "]";

    cout << os.str() << endl;
}

template <typename T>
void ndarray<T>::open_brackets(
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

template <typename T>
string ndarray<T>::print_2d(unsigned lpad) {
    unsigned n = shape[dim - 2];
    unsigned m = shape[dim - 1];

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
            out << this->at({i, j}) << sep1;
        }
        out << sep2;
        out << endl;
    }
    out << lpad_out << "]";

    string out_str = out.str();
    return out_str;
}

template <typename T>
void ndarray<T>::close_brackets(
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
/**********************************************************************************************************************/


/***********************************************************************************************************************
 *                                                  Broadcasting                                                       *
 **********************************************************************************************************************/
template <typename T>
T _arithmetic_op(const T &a, const T &b, ArithmeticOpEnum op) {
    T c;
    switch (op) {
        case ePlus:
            c = a + b;
            break;
        case eMinus:
            c = a - b;
            break;
        case eMultiplies:
            c = a * b;
            break;
        case eDiv:
            c = a / b;
            break;
        default:
            throw "Unknown operation";
    }

    return c;
}

template <typename T>
T _bitwise_op(const T &a, const T &b, BitwiseOpEnum op) {
    T c;
    switch (op) {
        case eAnd:
            c = a & b;
            break;
        case eOr:
            c = a | b;
            break;
        case eXor:
            c = a ^ b;
            break;
        case eShiftLeft:
            c = a << b;
            break;
        case eShiftRight:
            c = a >> b;
            break;
        default:
            throw "Unknown operation";
    }

    return c;
}

template <typename T>
bool _relational_op(const T &a, const T &b, RelationalOpEnum op) {
    bool c;
    switch (op) {
        case eEquals:
            c = a == b;
            break;
        case eNotEquals:
            c = a != b;
            break;
        case eGt:
            c = a > b;
            break;
        case eGtEquals:
            c = a >= b;
            break;
        case eLt:
            c = a < b;
            break;
        case eLtEquals:
            c = a <= b;
            break;
        default:
            throw "Unknown operation";
    }

    return c;
}
/**********************************************************************************************************************/
template <typename T>
ndarray<T> _arithmetic_aligned(ndarray<T> &a, ndarray<T> &b, ArithmeticOpEnum op) {
    T *c_data = new T[a.size];
    for (unsigned i = 0; i < a.size; i++) {
        c_data[i] = _arithmetic_op(a.data()[i], b.data()[i], op);
    }

    return ndarray<T>(c_data, a.shape);
}

template <typename T>
ndarray<T> _bitwise_aligned(ndarray<T> &a, ndarray<T> &b, BitwiseOpEnum op) {
    T *c_data = new T[a.size];
    for (unsigned i = 0; i < a.size; i++) {
        c_data[i] = _bitwise_op(a.data_[i], b.data_[i], op);
    }

    return ndarray<T>(c_data, a.shape);
}

template <typename T>
ndarray<bool> _relational_aligned(const ndarray<T> &a, const ndarray<T> &b, RelationalOpEnum op) {
    bool *c_data = new bool[a.size];
    for (unsigned i = 0; i < a.size; i++) {
        c_data[i] = _relational_op(a.data_[i], b.data_[i], op);
    }

    return ndarray<bool>(c_data, a.shape);
}
/**********************************************************************************************************************/
template <typename T>
bool _align_arrays(ndarray<T> &a, ndarray<T> &b) {
    unsigned dim_diff = abs(int(a.dim - b.dim));
    if(a.dim > b.dim) {
        for (unsigned i = 0; i < dim_diff; i++)
            b.shape.insert(b.shape.begin(), 1u);

        b.dim = a.dim;
        b._set_strides();
        return 0;
    } else {
        for (unsigned i = 0; i < dim_diff; i++)
            a.shape.insert(a.shape.begin(), 1u);

        a.dim = b.dim;
        a._set_strides();
        return 1;
    }
}

template <typename T>
void _unalign_array(ndarray<T> &a) {
    unsigned removed_axis = 0;
    for(unsigned i = 0; i < a.dim; i++) {
        if(a.shape[i] == 1)
            removed_axis++;
        else
            break;
    }

    a.shape.erase(a.shape.begin(), a.shape.begin() + removed_axis);
    a.dim -= removed_axis;
    a._set_strides();
}

template <typename T>
ndarray<T> _arithmetic_broadcast(ndarray<T> &a, ndarray<T> &b, ArithmeticOpEnum op) {
    ASSERT_SHAPES_MATCH(a.shape, b.shape);

    if (a.dim == b.dim && a.shape == b.shape) {
        return _arithmetic_aligned(a, b, op);
    }

    bool aligned_a;
    if (a.dim != b.dim) {
        aligned_a = _align_arrays(a, b);
    }

    vector<unsigned> final_shape(a.dim);
    for (unsigned i = 0; i < a.dim; i++) {
        final_shape[i] = max(a.shape[i], b.shape[i]);
    }
    ndarray<T> c(final_shape);

    vector<vector<unsigned>> c_indices;
    vector<unsigned> index_acumulator(c.dim, 0);
    _cartesian_product(final_shape, index_acumulator, c_indices);

    for (unsigned i = 0; i < c_indices.size(); i++) {
        vector<unsigned> result_indices = c_indices[i];
        vector<unsigned> aligned_a_indices = result_indices;
        vector<unsigned> aligned_b_indices = result_indices;

        for (unsigned j = 0; j < result_indices.size(); j++) {
            if (result_indices[j] > a.shape[j] - 1)
                aligned_a_indices[j] = a.shape[j] - 1;
        }
        for (unsigned j = 0; j < result_indices.size(); j++) {
            if (result_indices[j] > b.shape[j] - 1)
                aligned_b_indices[j] = b.shape[j] - 1;
        }

        T val_aligned_a = a.at(aligned_a_indices);
        T val_aligned_b = b.at(aligned_b_indices);
        c.at(result_indices) = _arithmetic_op(val_aligned_a, val_aligned_b, op);
    }

    if(aligned_a)
        _unalign_array(a);
    else
        _unalign_array(b);

    return c;
}

template <typename T>
ndarray<T> _bitwise_broadcast(ndarray<T> &a, ndarray<T> &b, BitwiseOpEnum op) {
    ASSERT_SHAPES_MATCH(a.shape, b.shape);

    if (a.dim == b.dim && a.shape == b.shape) {
        return _bitwise_aligned(a, b, op);
    }

    bool aligned_a;
    if (a.dim != b.dim) {
        aligned_a = _align_arrays(a, b);
    }

    vector<unsigned> final_shape(a.dim);
    for (unsigned i = 0; i < a.dim; i++) {
        final_shape[i] = max(a.shape[i], b.shape[i]);
    }
    ndarray<T> c(final_shape);

    vector<vector<unsigned>> c_indices;
    vector<unsigned> index_acumulator(c.dim, 0);
    _cartesian_product(final_shape, index_acumulator, c_indices);

    for (unsigned i = 0; i < c_indices.size(); i++) {
        vector<unsigned> result_indices = c_indices[i];
        vector<unsigned> aligned_a_indices = result_indices;
        vector<unsigned> aligned_b_indices = result_indices;

        for (unsigned j = 0; j < result_indices.size(); j++) {
            if (result_indices[j] > a.shape[j] - 1)
                aligned_a_indices[j] = a.shape[j] - 1;
        }
        for (unsigned j = 0; j < result_indices.size(); j++) {
            if (result_indices[j] > b.shape[j] - 1)
                aligned_b_indices[j] = b.shape[j] - 1;
        }

        T val_aligned_a = a.at(aligned_a_indices);
        T val_aligned_b = b.at(aligned_b_indices);

        c.at(result_indices) = _bitwise_op(val_aligned_a, val_aligned_b, op);
    }

    if(aligned_a)
        _unalign_array(a);
    else
        _unalign_array(b);

    return c;
}

template <typename T>
ndarray<bool> _relational_broadcast(ndarray<T> &a, ndarray<T> &b, RelationalOpEnum op) {
    ASSERT_SHAPES_MATCH(a.shape, b.shape);

    if (a.dim == b.dim && a.shape == b.shape) {
        return _relational_aligned(a, b, op);
    }

    bool aligned_a;
    if (a.dim != b.dim) {
        aligned_a = _align_arrays(a, b);
    }

    vector<unsigned> final_shape(a.dim);
    for (unsigned i = 0; i < a.dim; i++) {
        final_shape[i] = max(a.shape[i], b.shape[i]);
    }
    ndarray<bool> c(final_shape);

    vector<vector<unsigned>> c_indices;
    vector<unsigned> index_acumulator(c.dim, 0);
    _cartesian_product(final_shape, index_acumulator, c_indices);

    for (unsigned i = 0; i < c_indices.size(); i++) {
        vector<unsigned> result_indices = c_indices[i];
        vector<unsigned> aligned_a_indices = result_indices;
        vector<unsigned> aligned_b_indices = result_indices;

        for (unsigned j = 0; j < result_indices.size(); j++) {
            if (result_indices[j] > a.shape[j] - 1)
                aligned_a_indices[j] = a.shape[j] - 1;
        }
        for (unsigned j = 0; j < result_indices.size(); j++) {
            if (result_indices[j] > b.shape[j] - 1)
                aligned_b_indices[j] = b.shape[j] - 1;
        }

        T val_aligned_a = a.at(aligned_a_indices);
        T val_aligned_b = b.at(aligned_b_indices);
        c.at(result_indices) = _relational_op(val_aligned_a, val_aligned_b, op);
    }

    if(aligned_a)
        _unalign_array(a);
    else
        _unalign_array(b);

    return c;
}
/**********************************************************************************************************************/
