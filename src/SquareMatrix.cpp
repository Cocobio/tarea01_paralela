#include "SquareMatrix.hpp"

namespace vlsi {

template<class T>
SquareMatrix<T>::SquareMatrix(size_t dimension) {
    this->dim = dimension;
    this->data = new T[this->dim * this->dim];
    this->row_size = dimension;
    this->offset[0] = 0u;
    this->offset[1] = 0u;
}

template<class T>
SquareMatrix<T>::SquareMatrix(size_t dimension, T fill) {
    this->dim = dimension;
    this->data = new T[this->dim * this->dim];
    this->row_size = dimension;
    this->offset[0] = 0u;
    this->offset[1] = 0u;

    for (size_t i=0; i<this->dim; ++i)
        for (size_t j=0; j<this->dim; ++j)
            this->data[i*this->row_size + j] = fill;
}

template<class T>
SquareMatrix<T> SquareMatrix<T>::getView(size_t row_offset,
                                         size_t column_offset,
                                         size_t dim) {
    SquareMatrix<T> res;
    res.data = this->data;
    res.dim = dim;
    res.offset[0] = row_offset;
    res.offset[1] = column_offset;
    res.row_size = this->row_size;

    return res;
}

template<class T>
SquareMatrix<T>::~SquareMatrix() {
    if (this->offset[0] == 0 &&
        this->offset[1] == 0 &&
        this->row_size == this->dim)
        delete[] this->data;
}

template<class T>
T& SquareMatrix<T>::operator[](size_t i, size_t j) {
    return this->data[(this->offset[0]+i)*this->row_size + this->offset[1]+j];
}

} // vlsi
