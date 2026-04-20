#include "SquareMatrix.hpp"

SquareMatrix::SquareMatrix(size_t dimension) {
    this->dim = dimension;
    this->data = new T[this->dim * this->dim];
}
