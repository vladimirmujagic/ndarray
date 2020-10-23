#pragma once

#include <functional>
#include <algorithm>
#include <iostream>
#include <numeric>
#include <sstream>
#include <vector>
#include <memory>

#include "../include/ndarray_validation.hpp"
#include "../include/ndarray_utils.hpp"

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
    T* data_;
    
public:
    std::vector<unsigned> shape;
    unsigned size;
    unsigned dim;


private:
    void             _set_strides() {
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
    vector<unsigned> _next_cartesian_tuple(vector<unsigned> acc, vector<unsigned> sets) const {
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
    unsigned         _get_flat_index(const vector<unsigned> &indices) const {
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

    T                _arithmetic_op(const T &a, const T &b, ArithmeticOpEnum op) const {
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
    ndarray<T>       _arithmetic_aligned(const ndarray<T> &a, const ndarray<T> &b, ArithmeticOpEnum op) const {
        T *c_data = new T[a.size];
        for (unsigned i = 0; i < a.size; i++) {
            c_data[i] = _arithmetic_op(a.data_[i], b.data_[i], op);
        }

        return ndarray<T>(c_data, a.shape);
    }
    ndarray<T>       _arithmetic_broadcast(const ndarray<T> &a, const ndarray<T> &b, ArithmeticOpEnum op) const {
        ASSERT_SHAPES_MATCH(a.shape, b.shape);

        if (a.dim == b.dim && a.shape == b.shape) {
            return _arithmetic_aligned(a, b, op);
        }

        vector<unsigned> bigger_shape, smaller_shape, final_shape;
        ndarray<T> aligned_a, aligned_b;
        if (a.dim != b.dim) {
            if (a.dim < b.dim) {
                smaller_shape = a.shape;
                bigger_shape = b.shape;
            }
            if (b.dim < a.dim) {
                smaller_shape = b.shape;
                bigger_shape = a.shape;
            }

            unsigned dim_diff = bigger_shape.size() - smaller_shape.size();
            for (unsigned i = 0; i < dim_diff; i++) {
                smaller_shape.insert(smaller_shape.begin(), 1);
            }

            if (a.dim < b.dim) {
                aligned_a = ndarray<T>(a.data_, smaller_shape);
                aligned_b = b;
            }
            if (b.dim < a.dim) {
                aligned_b = ndarray<T>(b.data_, smaller_shape);
                aligned_a = a;
            }
        } else {
            aligned_a = a;
            aligned_b = b;
        }

        ndarray<T> c;
        for (unsigned i = 0; i < aligned_a.dim; i++) {
            if (aligned_a.shape[i] == aligned_b.shape[i])
                final_shape.push_back(aligned_a.shape[i]);
            else
                final_shape.push_back(max(aligned_a.shape[i], aligned_b.shape[i]));
        }
        c = ndarray<T>(final_shape);

        vector<vector<unsigned>> c_indices;
        vector<unsigned> index_acumulator(c.dim, 0);
        c._cartesian_product(final_shape, index_acumulator, c_indices);

        for (unsigned i = 0; i < c_indices.size(); i++) {
            vector<unsigned> result_indices = c_indices[i];
            vector<unsigned> aligned_a_indices;
            for (unsigned j = 0; j < result_indices.size(); j++) {
                if (result_indices[j] > aligned_a.shape[j] - 1)
                    aligned_a_indices.push_back(aligned_a.shape[j] - 1);
                else
                    aligned_a_indices.push_back(result_indices[j]);
            }
            vector<unsigned> aligned_b_indices;
            for (unsigned j = 0; j < result_indices.size(); j++) {
                if (result_indices[j] > aligned_b.shape[j] - 1)
                    aligned_b_indices.push_back(aligned_b.shape[j] - 1);
                else
                    aligned_b_indices.push_back(result_indices[j]);
            }

            T a_b_result;
            T val_aligned_a = aligned_a.at(aligned_a_indices);
            T val_aligned_b = aligned_b.at(aligned_b_indices);

            c.at(result_indices) = _arithmetic_op(val_aligned_a, val_aligned_b, op);
        }

        return c;
    }
    T                _bitwise_op(const T &a, const T &b, BitwiseOpEnum op) const {
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
    ndarray<T>       _bitwise_aligned(const ndarray<T> &a, const ndarray<T> &b, BitwiseOpEnum op) const {
        bool *c_data = new bool[a.size];
        for (unsigned i = 0; i < a.size; i++) {
            c_data[i] = _bitwise_op(a.data_[i], b.data_[i], op);
        }

        return ndarray<T>(c_data, a.shape);
    }
    ndarray<T>       _bitwise_broadcast(const ndarray<T> &a, const ndarray<T> &b, BitwiseOpEnum op) const {
        ASSERT_SHAPES_MATCH(a.shape, b.shape);

        if (a.dim == b.dim && a.shape == b.shape) {
            return _bitwise_aligned(a, b, op);
        }

        vector<unsigned> bigger_shape, smaller_shape, final_shape;
        ndarray<T> aligned_a, aligned_b;
        if (a.dim != b.dim) {
            if (a.dim < b.dim) {
                smaller_shape = a.shape;
                bigger_shape = b.shape;
            }
            if (b.dim < a.dim) {
                smaller_shape = b.shape;
                bigger_shape = a.shape;
            }

            unsigned dim_diff = bigger_shape.size() - smaller_shape.size();
            for (unsigned i = 0; i < dim_diff; i++) {
                smaller_shape.insert(smaller_shape.begin(), 1);
            }

            if (a.dim < b.dim) {
                aligned_a = ndarray<T>(a.data_, smaller_shape);
                aligned_b = b;
            }
            if (b.dim < a.dim) {
                aligned_b = ndarray<T>(b.data_, smaller_shape);
                aligned_a = a;
            }
        } else {
            aligned_a = a;
            aligned_b = b;
        }

        ndarray<T> c;
        for (unsigned i = 0; i < aligned_a.dim; i++) {
            if (aligned_a.shape[i] == aligned_b.shape[i])
                final_shape.push_back(aligned_a.shape[i]);
            else
                final_shape.push_back(max(aligned_a.shape[i], aligned_b.shape[i]));
        }
        c = ndarray<T>(final_shape);

        vector<vector<unsigned>> c_indices;
        vector<unsigned> index_acumulator(c.dim, 0);
        c._cartesian_product(final_shape, index_acumulator, c_indices);

        for (unsigned i = 0; i < c_indices.size(); i++) {
            vector<unsigned> result_indices = c_indices[i];
            vector<unsigned> aligned_a_indices;
            for (unsigned j = 0; j < result_indices.size(); j++) {
                if (result_indices[j] > aligned_a.shape[j] - 1)
                    aligned_a_indices.push_back(aligned_a.shape[j] - 1);
                else
                    aligned_a_indices.push_back(result_indices[j]);
            }
            vector<unsigned> aligned_b_indices;
            for (unsigned j = 0; j < result_indices.size(); j++) {
                if (result_indices[j] > aligned_b.shape[j] - 1)
                    aligned_b_indices.push_back(aligned_b.shape[j] - 1);
                else
                    aligned_b_indices.push_back(result_indices[j]);
            }

            T a_b_result;
            T val_aligned_a = aligned_a.at(aligned_a_indices);
            T val_aligned_b = aligned_b.at(aligned_b_indices);

            c.at(result_indices) = _bitwise_op(val_aligned_a, val_aligned_b, op);
        }

        return c;
    }
    bool             _relational_op(const T &a, const T &b, RelationalOpEnum op) const {
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
    ndarray<bool>    _relational_aligned(const ndarray<T> &a, const ndarray<T> &b, RelationalOpEnum op) const {
        bool *c_data = new bool[a.size];
        for (unsigned i = 0; i < a.size; i++) {
            c_data[i] = _relational_op(a.data_[i], b.data_[i], op);
        }

        return ndarray<bool>(c_data, a.shape);
    }
    ndarray<bool>    _relational_broadcast(const ndarray<T> &a, const ndarray<T> &b, RelationalOpEnum op) const {
        ASSERT_SHAPES_MATCH(a.shape, b.shape);

        if (a.dim == b.dim && a.shape == b.shape) {
            return _relational_aligned(a, b, op);
        }

        vector<unsigned> bigger_shape, smaller_shape, final_shape;
        ndarray<T> aligned_a, aligned_b;
        if (a.dim != b.dim) {
            if (a.dim < b.dim) {
                smaller_shape = a.shape;
                bigger_shape = b.shape;
            }
            if (b.dim < a.dim) {
                smaller_shape = b.shape;
                bigger_shape = a.shape;
            }

            unsigned dim_diff = bigger_shape.size() - smaller_shape.size();
            for (unsigned i = 0; i < dim_diff; i++) {
                smaller_shape.insert(smaller_shape.begin(), 1);
            }

            if (a.dim < b.dim) {
                aligned_a = ndarray<T>(a.data_, smaller_shape);
                aligned_b = b;
            }
            if (b.dim < a.dim) {
                aligned_b = ndarray<T>(b.data_, smaller_shape);
                aligned_a = a;
            }
        } else {
            aligned_a = a;
            aligned_b = b;
        }

        for (unsigned i = 0; i < aligned_a.dim; i++) {
            if (aligned_a.shape[i] == aligned_b.shape[i])
                final_shape.push_back(aligned_a.shape[i]);
            else
                final_shape.push_back(max(aligned_a.shape[i], aligned_b.shape[i]));
        }
        ndarray<bool> c(final_shape);

        vector<vector<unsigned>> c_indices;
        vector<unsigned> index_acumulator(c.dim, 0);
        c._cartesian_product(final_shape, index_acumulator, c_indices);

        for (unsigned i = 0; i < c_indices.size(); i++) {
            vector<unsigned> result_indices = c_indices[i];
            vector<unsigned> aligned_a_indices;
            for (unsigned j = 0; j < result_indices.size(); j++) {
                if (result_indices[j] > aligned_a.shape[j] - 1)
                    aligned_a_indices.push_back(aligned_a.shape[j] - 1);
                else
                    aligned_a_indices.push_back(result_indices[j]);
            }
            vector<unsigned> aligned_b_indices;
            for (unsigned j = 0; j < result_indices.size(); j++) {
                if (result_indices[j] > aligned_b.shape[j] - 1)
                    aligned_b_indices.push_back(aligned_b.shape[j] - 1);
                else
                    aligned_b_indices.push_back(result_indices[j]);
            }

            T a_b_result;
            T val_aligned_a = aligned_a.at(aligned_a_indices);
            T val_aligned_b = aligned_b.at(aligned_b_indices);

            c.at(result_indices) = _relational_op(val_aligned_a, val_aligned_b, op);
        }

        return c;
    }

public:
    void _cartesian_product(vector<unsigned> sets, vector<unsigned> &acc, vector<vector<unsigned>> &cp) const {

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
    /*************************************************************************
    *                    Construction / Destruction                          *
    *************************************************************************/
    // TODO fix check data size
    ndarray() {

    }
    ~ndarray() {
        delete[] data_;
    }
    ndarray(const ndarray<T> &copy) {
        this->dim = copy.dim;
        this->shape = copy.shape;
        this->strides_ = copy.strides_;
        this->size = copy.size;

        T* data_copy = new T[copy.size];
        for(unsigned i = 0; i < copy.size; i ++) {
            data_copy[i] = copy.data_[i];
        }
        this->data_ = data_copy;
    }
    ndarray<T>& operator=(const ndarray<T> &a) {
        this->dim = a.dim;
        this->shape = a.shape;
        this->strides_ = a.strides_;
        this->size = a.size;

        T* data_copy = new T[a.size];
        for(unsigned i = 0; i < a.size; i ++) {
            data_copy[i] = a.data_[i];
        }
        this->data_ = data_copy;

        return *this;
    }
    ndarray(const vector<unsigned> &shape)
        : shape(shape)
    {
        ASSERT_CONDITION(!shape.empty(),"shape is not allowed to be empty");

        const unsigned shape_product = accumulate(shape.begin(), shape.end(), 1, multiplies<unsigned>());
        size  = shape_product;
        dim   = shape.size();
        T *data = new T[shape_product];
        for(unsigned i = 0; i < size; i++) {
            data[i] = 0;
        }
        data_ = data;

        _set_strides();
    }
    ndarray(const T &v, const vector<unsigned> &shape)
        : shape(shape)
    {
        ASSERT_CONDITION(!shape.empty(),"shape is not allowed to be empty");

        const unsigned shape_product = accumulate(shape.begin(), shape.end(), 1, multiplies<unsigned>());
        size  = shape_product;
        dim   = shape.size();
        T *data = new T[shape_product];
        for(unsigned i = 0; i < size; i++) {
            data[i] = v;
        }
        data_ = data;

        _set_strides();
    }
    ndarray(T *data, const vector<unsigned> &shape)
        : shape(shape)
    {
        ASSERT_CONDITION(!shape.empty(),"shape is not allowed to be empty");

        const unsigned shape_product = accumulate(shape.begin(), shape.end(), 1, multiplies<unsigned>());
        size = shape_product;
        dim = shape.size();
        T* data_copy = new T[shape_product];
        for(unsigned i = 0; i < size; i++) {
            data_copy[i] = data[i];
        }
        data_ = data_copy;

        _set_strides();
    }
    /*************************************************************************/

    /*************************************************************************
    *                       Attributes Get / Set                             *
    *************************************************************************/
    T*               data()    { return data_; }
    vector<unsigned> strides() { return strides_; }
    /************************************************************************/

    /*************************************************************************
    *                    (i, j, k, ...) get and set                          *
    *************************************************************************/
    template<typename... I>
    T           operator()(I... indices) const {
        vector<unsigned> is = {(unsigned)indices...};
        unsigned index = this->_get_flat_index(is);

        return this->data_[index];
    }
    template<typename... I>
    T&          operator()(I... indices) {
        vector<unsigned> is = {(unsigned)indices...};
        unsigned index = this->_get_flat_index(is);

        return this->data_[index];
    }
    T           at(const vector<unsigned> &indices) const {
        unsigned index = this->_get_flat_index(indices);

        return this->data_[index];
    }
    T&          at(const vector<unsigned> &indices) {
        unsigned index = this->_get_flat_index(indices);

        return this->data_[index];
    }
    ndarray<T>  subarray_at(const vector<unsigned> &indices) const {
        const unsigned indices_size = indices.size();
        const unsigned shape_size = this->shape.size();

        ASSERT_CONDITION(indices_size >= 1 && indices_size <= this->dim - 1,
                         "Number of indices must be between 1 and dim-1");
        ASSERT_INDICES_IN_RANGE(this->shape, indices);

        if(this->dim == 2) {
            return ndarray<T>(this->data_ + (indices[0] * this->shape[1]), {this->shape[1]});
        }

        unsigned index = 0;
        for(unsigned i = 0; i < indices.size(); i++) {
            index += indices[i] * this->strides_[i];
        }

        vector<unsigned> new_shape;
        for(unsigned i = indices_size; i < shape_size; i++) {
            new_shape.push_back(this->shape[i]);
        }

        T *start = this->data_ + index;
        return ndarray<T>(start, new_shape);
    }
    ndarray<T>  copy_subarray_at(const vector<unsigned> &indices) const {
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
        copy(start, end, slice);

        return ndarray<T>(slice, new_shape);
    }
    /*************************************************************************/

    /*************************************************************************
    *                       Arithmetic operators                             *
    *************************************************************************/
    ndarray<T>  operator+(ndarray<T> a) const {
        return this->_arithmetic_broadcast(*this, a, ePlus);
    }
    ndarray<T>& operator+=(const ndarray<T> &a) {
        *this = this->_arithmetic_broadcast(*this, a, ePlus);

        return *this;
    }
    ndarray<T>& operator+=(const T &v) {
        for(unsigned i = 0; i < this->size; i++) {
            this->data_[i] += v;
        }

        return *this;
    }
    ndarray<T>  operator-(ndarray<T> a) const {
        return this->_arithmetic_broadcast(*this, a, eMinus);
    }
    ndarray<T>& operator-=(const ndarray<T> &a) {
        *this = this->_arithmetic_broadcast(*this, a, eMinus);

        return *this;
    }
    ndarray<T>& operator-=(const T &v) {
        for(unsigned i = 0; i < this->size; i++) {
            this->data_[i] -= v;
        }

        return *this;
    }
    ndarray<T>  operator*(ndarray<T> a) const {
        return this->_arithmetic_broadcast(*this, a, eMultiplies);
    }
    ndarray<T>& operator*=(const ndarray<T> &a) {
        *this = this->_arithmetic_broadcast(*this, a, eMultiplies);

        return *this;
    }
    ndarray<T>& operator*=(const T &v) {
        for(unsigned i = 0; i < this->size; i++) {
            this->data_[i] *= v;
        }

        return *this;
    }
    ndarray<T>  operator/(ndarray<T> a) const {
        return this->_arithmetic_broadcast(*this, a, eDiv);
    }
    ndarray<T>& operator/=(const ndarray<T> &a) {
        *this = this->_arithmetic_broadcast(*this, a, eDiv);

        return *this;
    }
    ndarray<T>& operator/=(const T &v) {
        for(unsigned i = 0; i < this->size; i++) {
            this->data_[i] /= v;
        }

        return *this;
    }
    /************************************************************************/

    /*************************************************************************
    *                       Bitwise operators                                *
    *************************************************************************/
    ndarray<T>  operator&(ndarray<T> a) const {
        return this->_bitwise_broadcast(*this, a, eAnd);

    }
    ndarray<T>& operator&=(const ndarray<T> &a) {
        *this = this->_bitwise_broadcast(*this, a, eAnd);

    }
    ndarray<T>& operator&=(const T &v) {
        for(unsigned i = 0; i < this->size; i++) {
            this->data_[i] &= v;
        }

        return *this;
    }
    ndarray<T>  operator|(ndarray<T> a) const {
        return this->_bitwise_broadcast(*this, a, eOr);
    }
    ndarray<T>& operator|=(const ndarray<T> &a) {
        *this = this->_bitwise_broadcast(*this, a, eOr);
    }
    ndarray<T>& operator|=(const T &v) {
        for(unsigned i = 0; i < this->size; i++) {
            this->data_[i] |= v;
        }

        return *this;
    }
    ndarray<T>  operator^(ndarray<T> a) const {
        return this->_bitwise_broadcast(*this, a, eXor);
    }
    ndarray<T>& operator^=(const ndarray<T> &a) {
        *this = this->_bitwise_broadcast(*this, a, eXor);
    }
    ndarray<T>& operator^=(const T &v) {
        for(unsigned i = 0; i < this->size; i++) {
            this->data_[i] ^= v;
        }

        return *this;
    }
    ndarray<T>  operator>>(ndarray<T> a) const {
        return this->_bitwise_broadcast(*this, a, eShiftRight);

    }
    ndarray<T>& operator>>(const ndarray<T> &a) {
        *this = this->_bitwise_broadcast(*this, a, eShiftRight);

    }
    ndarray<T>& operator>>=(const T &v) {
        for(unsigned i = 0; i < this->size; i++) {
            this->data_[i] >>= v;
        }

        return *this;
    }
    ndarray<T>  operator<<(ndarray<T> a) const {
        return this->_bitwise_broadcast(*this, a, eShiftLeft);

    }
    ndarray<T>& operator<<(const ndarray<T> &a) {
        *this = this->_bitwise_broadcast(*this, a, eShiftLeft);

    }
    ndarray<T>& operator<<=(const T &v) {
        for(unsigned i = 0; i < this->size; i++) {
            this->data_[i] <<= v;
        }

        return *this;
    }
    ndarray<T>  operator~() {
        for(unsigned i = 0; i < this->size; i++) {
            this->data_[i] = ~this->data[i];
        }

        return *this;
    }
    /************************************************************************/

    /************************************************************************
    *                      Relational operators                             *
    ************************************************************************/
    bool          equals(const ndarray<T> &a) const {
        ASSERT_CONDITION(a.size == this->size && a.shape == this->shape,
        "Only arrays with same shape and size can be compared");

        for(unsigned i = 0; i < this->size; i++) {
            if(this->data_[i] != a.data_[i]) {
                return false;
            }
        }

        return true;
    }
    ndarray<bool> operator==(const ndarray<T> &a) const {
        return this->_relational_broadcast(*this, a, eEquals);
    }
    ndarray<bool> operator==(const T &s) const {
        bool *r = new bool[this->size];
        for(unsigned i = 0; i < this->size; i++) {
            r[i] = this->data_[i] == s;
        }

        return ndarray<bool>(r, this->shape);
    }
    ndarray<bool> operator!=(const ndarray<T> &a) const {
        return this->_relational_broadcast(*this, a, eNotEquals);
    }
    ndarray<bool> operator!=(const T &s) const {
        bool *r = new bool[this->size];
        for(unsigned i = 0; i < this->size; i++) {
            r[i] = this->data_[i] != s;
        }

        return ndarray<bool>(r, this->shape);
    }
    ndarray<bool> operator>(const ndarray<T> &a) const {
        return this->_relational_broadcast(*this, a, eGt);
    }
    ndarray<bool> operator>(const T &s) const {
        bool *r = new bool[this->size];
        for(unsigned i = 0; i < this->size; i++) {
            r[i] = this->data_[i] > s;
        }

        return ndarray<bool>(r, this->shape);
    }
    ndarray<bool> operator>=(const ndarray<T> &a) const {
        return this->_relational_broadcast(*this, a, eGtEquals);
    }
    ndarray<bool> operator>=(const T &s) const {
        bool *r = new bool[this->size];
        for(unsigned i = 0; i < this->size; i++) {
            this->data_[i] = this->data_[i] >= s;
        }

        return ndarray<bool>(r, this->shape);
    }
    ndarray<bool> operator<(const ndarray<T> &a) const {
        return this->_relational_broadcast(*this, a, eLt);
    }
    ndarray<bool> operator<(const T &s) const {
        bool *r = new bool[this->size];
        for(unsigned i = 0; i < this->size; i++) {
            this->data_[i] = this->data_[i] < s;
        }

        return ndarray<bool>(r, this->shape);
    }
    ndarray<bool> operator<=(const ndarray<T> &a) const {
        return this->_relational_broadcast(*this, a, eLtEquals);
    }
    ndarray<bool> operator<=(const T &s) const {
        bool *r = new bool[this->size];
        for(unsigned i = 0; i < this->size; i++) {
            this->data_[i] = this->data_[i] <= s;
        }

        return ndarray<bool>(r, this->shape);
    }
    /***********************************************************************/

    /************************************************************************
    *                      API functions                                    *
    ************************************************************************/
    void reshape(const vector<unsigned> &new_shape) {
        unsigned p = accumulate(new_shape.begin(), new_shape.end(), 1, multiplies<unsigned>());

        ASSERT_CONDITION(this->size == p,
        "When reshaping, new shape product must be equal to target ndarray size");

        this->shape = new_shape;
        this->dim = new_shape.size();
        _set_strides();
    }
    /***********************************************************************/

    /**********************************************************************
    *                    Print related functions                         *
    **********************************************************************/
    void print() {
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
            this->_cartesian_product(new_shape, index_acumulator, all_matrix_indices);

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
    string print_2d(unsigned lpad=0) {
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
    /***********************************************************************/
};

