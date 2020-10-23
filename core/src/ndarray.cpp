//#include <functional>
//#include <algorithm>
//#include <numeric>
//#include <sstream>
//#include <vector>
//
//#include "../include/ndarray.hpp"
//#include "../include/ndarray_utils.hpp"
//#include "../include/ndarray_validation.hpp"
//
//
//using namespace std;
//
//
//
//
///***********************************************************************************************************************
// *                                            Print related functions                                                  *
// **********************************************************************************************************************/
//template <typename T>
//string print_2d(const ndarray<T> &b, unsigned lpad) {
//    unsigned b_size = b.shape.size();
//    unsigned n = b.shape[b_size - 2];
//    unsigned m = b.shape[b_size - 1];
//
//    ostringstream out;
//    string sp_out = string(lpad, ' ');
//    string sp_in = string(lpad + 1, ' ');
//    string lpad_out = lpad == 0 ? "" : sp_out;
//    string lpad_in = lpad == 0 ? " " : sp_in;
//
//    out << lpad_out << "[\n";
//    for(unsigned i = 0; i < n; i++) {
//        out << lpad_in << "[";
//        string sep2 = i == n - 1 ? "]" : "], ";
//        for(unsigned j = 0; j < m; j++) {
//            string sep1 = j == m - 1 ? "" : ", ";
//            out << b(i, j) << sep1;
//        }
//        out << sep2;
//        out << endl;
//    }
//    out << lpad_out << "]";
//
//    string out_str = out.str();
//    return out_str;
//}
//
//template <typename T>
//ostream& operator<<(ostream &os, const ndarray<T> &a) {
//    unsigned dim = a.dim;
//    vector<unsigned> shape = a.shape;
//
//    if(dim == 1) {
//        string sep;
//
//        os << "[";
//        for(unsigned i = 0; i < a.size; i++) {
//            sep = i == a.size - 1 ? "" : ", ";
//            os << a.data_[i] << sep;
//        }
//        os << "]";
//    } else if(dim == 2) {
//        os << print_2d(a);
//    } else if (dim == 3) {
//        os << "[\n";
//        for(unsigned i = 0; i < shape[0]; i++) {
//            ndarray<T> curr_a = a.subarray_at({i});
//            os << print_2d(curr_a, 1) << endl;
//        }
//        os << "]";
//    } else {
//        vector<unsigned> new_shape;
//        new_shape.reserve(dim - 2);
//        for(unsigned i = 0; i < dim - 2; i++) {
//            new_shape.push_back(shape[i]);
//        }
//
//        vector<vector<unsigned>> all_matrix_indices;
//        vector<unsigned> index_acumulator(dim - 2, 0);
//        a._cartesian_product(new_shape, index_acumulator, all_matrix_indices);
//
//        vector<unsigned> prev_indices;
//        vector<unsigned> next_indices;
//        vector<unsigned> curr_indices;
//        unsigned n = all_matrix_indices.size();
//        for(int i = 0; i < all_matrix_indices.size(); i++) {
//            curr_indices = all_matrix_indices[i];
//            prev_indices = i == 0 ?
//                all_matrix_indices[i] : all_matrix_indices[i - 1];
//            next_indices = i != all_matrix_indices.size() - 1 ?
//                all_matrix_indices[i + 1] : all_matrix_indices[i];
//
//            ndarray<T> curr_b = a.subarray_at({curr_indices});
//
//            open_brackets(os, i, curr_indices, prev_indices, next_indices);
//            os << print_2d(curr_b, dim - 2) << endl;
//            close_brackets(os, i, n, shape, curr_indices, prev_indices, next_indices);
//        }
//    }
//    os << endl;
//
//    string sep;
//    os << "dim=" << a.dim << " shape=[";
//    for(int i = 0; i < dim; i++) {
//        sep = i == dim - 1 ? "" : ", ";
//        os << shape[i] << sep;
//    }
//    os << "]";
//
//    os << " strides=[";
//    for(int i = 0; i < a.strides_.size(); i++) {
//        sep = i == a.strides_.size() - 1 ? "" : ", ";
//        os << a.strides_[i] << sep;
//    }
//    os << "]";
//
//    return os;
//}
///**********************************************************************************************************************/
//
//
///***********************************************************************************************************************
// *                                            Template declarations                                                    *
// **********************************************************************************************************************/
//template class ndarray<unsigned char>;
//template class ndarray<float>;
//template class ndarray<bool>;
//
//template ostream& operator<< <float>(ostream&, const ndarray<float>&);
//template ostream& operator<< <bool>(ostream&, const ndarray<bool>&);
//
//template float& ndarray<float>::operator()<int>(int);
//template float& ndarray<float>::operator()<int, int>(int, int);
//template float& ndarray<float>::operator()<int, int, int>(int, int, int);
//template float& ndarray<float>::operator()<int, int, int, int>(int, int, int, int);
//template float& ndarray<float>::operator()<int, int, int, int, int>(int, int, int, int, int);
//
//template float& ndarray<float>::operator()<unsigned int>(unsigned int);
//template float& ndarray<float>::operator()<unsigned int, unsigned int>(unsigned int, unsigned int);
//template float& ndarray<float>::operator()<unsigned int, unsigned int, unsigned int>(unsigned int, unsigned int, unsigned int);
//template float& ndarray<float>::operator()<unsigned int, unsigned int, unsigned int, unsigned int>(unsigned int, unsigned int, unsigned int, unsigned int);
//template float& ndarray<float>::operator()<unsigned int, unsigned int, unsigned int, unsigned int, unsigned int>(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int);
///**********************************************************************************************************************/
//
