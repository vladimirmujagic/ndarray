#pragma once

#include <iostream>
#include <vector>


template<typename T>
class ndarray {
    private:
        T* data;
    public:
        std::vector<unsigned> strides;
        std::vector<unsigned> shape;
        unsigned size;
        unsigned dim;

    private:
        void cartesian_product(
            std::vector<unsigned> shp,
            std::vector<unsigned> &acc,
            std::vector<std::vector<unsigned>> &result
        ) const;

        unsigned get_flat_index(const std::vector<unsigned> &indices) const;
        ndarray<T> element_wise(const ndarray<T> &a, const ndarray<T> &b, std::string op) const;

    public:
        ndarray();
        ndarray(const std::vector<unsigned> &shape);
        ndarray(T *data, const std::vector<unsigned> &shape);

        /* (i, j, k, ...) get and set  */
        template<typename... A>
        T           operator()(A... args) const;
        template<typename... A>
        T&          operator()(A... args);
        T           at(const std::vector<unsigned> &indices) const;
        T&          at(const std::vector<unsigned> &indices);

        void       reshape(const std::vector<unsigned> &new_shape);
        ndarray<T> subarray_at(const std::vector<unsigned> &indices) const;
        ndarray<T> copy_subarray_at(const std::vector<unsigned> &indices) const;

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

        ndarray<bool> operator>(const ndarray<T> &a) const;
        ndarray<bool> operator>(const T &s) const;
        ndarray<bool> operator>=(const ndarray<T> &a) const;
        ndarray<bool> operator>=(const T &s) const;
        ndarray<bool> operator<(const ndarray<T> &a) const;
        ndarray<bool> operator<(const T &s) const;
        ndarray<bool> operator<=(const ndarray<T> &a) const;
        ndarray<bool> operator<=(const T &s) const;

        template<typename U>
        friend std::ostream& operator<<(std::ostream &os, const ndarray<U> &a);
};

template<typename T>
std::string print_2d(const ndarray<T> &b, unsigned lpad=0);
template<typename T>
std::ostream& operator<<(std::ostream &os, const ndarray<T> &a);

