#include <cstdlib>
#include <iostream>
#include "src/TileMultiplication.cpp"

int main() {
    std::cout << "Multiplicacion por tiles/bloques usando solo punteros:\n";
    float A[16] = { 1, 2, 2, 1,
                    1, 1, 2, 3,
                    0, 1, 1, 0,
                    2, 0, 0, 1};

    float B[16] = { 0, 0, 1, 0,
                    0, 3, 1, 0,
                    1, 0, 2, 0,
                    0, 1, 0, 0};

    float C[16];
    // tile_multiplication(nullptr, nullptr, nullptr, 4, 2);
    tile_multiplication(A, B, C, 4, 4);
    for (int i=0; i<4; ++i) {
        for (int j=0; j<4; ++j)
            std::cout << C[i*4+j] << " ";
        std::cout << std::endl;
    }

    std::cout << "Multiplicacion por tiles/bloques usando vlsi::SquareMatrix<float>:\n";
    // Migrando a SquareMatrix
    vlsi::SquareMatrix<float> a(4), b(4);
    for (int i=0; i<4; ++i) {
        for (int j=0; j<4; ++j) {
            a[i,j] = A[i*4+j];
            b[i,j] = B[i*4+j];
        }
    }
    
    vlsi::SquareMatrix<float> c = tile_multiplication(a, b);

    for (int i=0; i<4; ++i) {
        for (int j=0; j<4; ++j)
            std::cout << c[i,j] << " ";
        std::cout << std::endl;
    }
    
    return 0;
}
