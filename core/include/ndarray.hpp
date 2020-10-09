#pragma once

#include <iostream>
#include <vector>

#ifndef NDEBUG
#   define ASSERT_CONDITION(Expr, Msg) \
    M_ASSERT(#Expr, Expr, __FILE__, __LINE__, Msg)
#else
#   define ASSERT_CONDITION(Expr, Msg) ;
#endif


void M_ASSERT(const char* expr_str, bool expr, const char* file, int line, const char* msg);

template<typename T>
class ndarray {
public:
    std::vector<unsigned> shape;
    std::vector<unsigned> shape_products;

    unsigned size;
    unsigned dim;
    T* data;

public:
    /* Construction */
    ndarray(const std::vector<unsigned> &shape);
    ndarray(T *data, const std::vector<unsigned> &shape);

    /* View sub array at index (i, j, k, ...) */
    ndarray<T> at(const std::vector<unsigned> &indices) const;

    /* Copy sub array at index (i, j, k, ...) */
    ndarray<T> copy_at(const std::vector<unsigned> &indices) const;

    void reshape(const std::vector<unsigned> &new_shape);

    /* (i, j, k, ...) get and set */
    template<typename... A>
    T           operator()(A... args) const;
    template<typename... A>
    T&          operator()(A... args);
    bool        operator==(ndarray<T> arh);
    ndarray<T>  operator+(ndarray<T> a) const;
    ndarray<T>& operator+=(const ndarray<T> &a);
    ndarray<T>& operator+=(const T &v);
    ndarray<T>  operator-(ndarray<T> a) const;
    ndarray<T>& operator-=(const ndarray<T> &a);
    ndarray<T>& operator-=(const T &v);
    ndarray<T>  operator*(ndarray<T> a) const;
    ndarray<T>& operator*=(const ndarray<T> &a);
    ndarray<T>& operator*=(const T &v);
    ndarray<T>  operator/(ndarray<T> a) const;
    ndarray<T>& operator/=(const ndarray<T> &a);
    ndarray<T>& operator/=(const T &v);
    template<typename U>
    friend std::ostream& operator<<(std::ostream &os, const ndarray<U> &a);
    
    void generate_indices(
        std::vector<unsigned> shp,
        std::vector<unsigned> &acc,
        std::vector<std::vector<unsigned>> &result
    ) const;
};

template<typename T>
std::string print_2d(const ndarray<T> &b, unsigned lpad=0);

template<typename T>
std::ostream& operator<<(std::ostream &os, const ndarray<T> &a);

