#pragma once

namespace vlsi {

template <class T>
class SquareMatrix {
// private:
public:
    T* data;
    size_t dim;
    size_t row_size;
    size_t offset[2];
    size_t id;

public:
    SquareMatrix() {};
    SquareMatrix(size_t dimension);
    SquareMatrix(size_t dimension,size_t id);
    SquareMatrix(size_t dimension, T fill);
    SquareMatrix(size_t dimension, T fill);

    ~SquareMatrix();

    SquareMatrix<T> getView(size_t row_offset, size_t column_offset, size_t dim);

    T& operator[](size_t i, size_t j);
    bool operator==(const SquareMatrix<T>& other) const;
};

} // vlsi
