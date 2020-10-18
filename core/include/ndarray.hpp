#pragma once

#include <iostream>
#include <vector>


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
        void _set_strides();
        void _cartesian_product(
            std::vector<unsigned> shp,
            std::vector<unsigned> &acc,
            std::vector<std::vector<unsigned>> &result
        ) const;
        unsigned   _get_flat_index(const std::vector<unsigned> &indices) const;
        ndarray<T> _element_wise(const ndarray<T> &a, const ndarray<T> &b, std::string op) const;

    public:
        /*************************************************************************
        *                    Construction / Destruction                          *
        *************************************************************************/
        ndarray();
        // ~ndarray();
        ndarray(const std::vector<unsigned> &shape);
        ndarray(const T &v, const std::vector<unsigned> &shape);
        ndarray(T *data, const std::vector<unsigned> &shape);
        /*************************************************************************/

        /*************************************************************************
        *                       Attributes Get / Set                             *
        *************************************************************************/
        T*                    data();
        std::vector<unsigned> strides();
        /************************************************************************/

        /*************************************************************************
        *                    (i, j, k, ...) get and set                          *
        *************************************************************************/
        template<typename... A>
        T           operator()(A... args) const;
        template<typename... A>
        T&          operator()(A... args);
        T           at(const std::vector<unsigned> &indices) const;
        T&          at(const std::vector<unsigned> &indices);

        ndarray<T> subarray_at(const std::vector<unsigned> &indices) const;
        ndarray<T> copy_subarray_at(const std::vector<unsigned> &indices) const;
        /*************************************************************************/

        /*************************************************************************
        *                       Arithmetic operators                             *
        *************************************************************************/
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
        /************************************************************************/

        /************************************************************************
        *                      Relational operators                             *
        ************************************************************************/
        bool       equals(const ndarray<T> &a) const;
        ndarray<T> operator==(const ndarray<T> &a) const;
        ndarray<T> operator==(const T &s) const;
        ndarray<T> operator!=(const ndarray<T> &a) const;
        ndarray<T> operator!=(const T &s) const;
        ndarray<T> operator>(const ndarray<T> &a) const;
        ndarray<T> operator>(const T &s) const;
        ndarray<T> operator>=(const ndarray<T> &a) const;
        ndarray<T> operator>=(const T &s) const;
        ndarray<T> operator<(const ndarray<T> &a) const;
        ndarray<T> operator<(const T &s) const;
        ndarray<T> operator<=(const ndarray<T> &a) const;
        ndarray<T> operator<=(const T &s) const;
        /**********************************************************************/

        /************************************************************************
        *                      API functions                                    *
        ************************************************************************/
        void       reshape(const std::vector<unsigned> &new_shape);
        /*************************************************************************/

        /**********************************************************************
        *                    Print related functions                         *
        **********************************************************************/
        template<typename U>
        friend std::ostream& operator<<(std::ostream &os, const ndarray<U> &a);
};
template<typename T>
std::string print_2d(const ndarray<T> &b, unsigned lpad=0);
template<typename T>
std::ostream& operator<<(std::ostream &os, const ndarray<T> &a);
/*****************************************************************************/
