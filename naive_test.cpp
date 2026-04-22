#include <cstdlib>
#include <iostream>
#include "src/naive.cpp"

int main() {
    float A[16] = { 1, 2, 2, 1,
                    1, 1, 2, 3,
                    0, 1, 1, 0,
                    2, 0, 0, 1};

    float B[16] = { 0, 0, 1, 0,
                    0, 3, 1, 0,
                    1, 0, 2, 0,
                    0, 1, 0, 0};

    std::cout << "Multiplicacion naive usando vlsi::SquareMatrix<float>:\n";
    // Migrando a SquareMatrix
    vlsi::SquareMatrix<float> a(4), b(4);
    for (int i=0; i<4; ++i) {
        for (int j=0; j<4; ++j) {
            a[i,j] = A[i*4+j];
            b[i,j] = B[i*4+j];
        }
    }
    
    vlsi::SquareMatrix<float> c = naive_multiplication(a, b);

    for (int i=0; i<4; ++i) {
        for (int j=0; j<4; ++j)
            std::cout << c[i,j] << " ";
        std::cout << std::endl;
    }
    
    return 0;
}
