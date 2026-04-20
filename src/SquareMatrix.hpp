#pragma once

#include <cstdlib>

class SquareMatrix {
private:
    typedef float T;
    T* data;
    size_t dim;

public:
    SquareMatrix(size_t dimension);
};


