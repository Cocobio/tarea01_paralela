#include <cstdlib>
#include <iostream>
#include "../../src/TileMultiplication.cpp"
#include "../../src/matrix.cpp"
#include <omp.h>

int main(int argn, char** argv) {
    int N = atoi(argv[1]);
    int tile = atoi(argv[2]);

    // Tecnicamente, un bloque de memoria sin inicializar es random :p
    float* A = (float*)malloc(N*N*sizeof(float));
    float* B = (float*)malloc(N*N*sizeof(float));
    float* C = (float*)malloc(N*N*sizeof(float));

    double time = medir([&]() {tile_multiplication(A, B, C, N, tile);});
    std::cout << "Measure time: " << time << std::endl;

    free(A);
    free(B);
    free(C);

    return 0;
}
