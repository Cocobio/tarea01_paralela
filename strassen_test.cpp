#include <cstdlib>
#include <iostream>
#include "src/strassen.cpp"
#include "src/matrix.cpp"

int main(int argn, char** argv) {
    int N = atoi(argv[1]);
    int base_case = atoi(argv[2]);

    float* A = (float*)malloc(N*N*sizeof(float));
    float* B = (float*)malloc(N*N*sizeof(float));
    float* C = (float*)malloc(N*N*sizeof(float));

    // Tecnicamente, un bloque de memoria sin inicializar es random :p

    // tile_multiplication(nullptr, nullptr, nullptr, 4, 2);
    double time = medir([&]() {strassen(A, B, C, N, base_case);});
    std::cout << "Measure time: " << time << std::endl;

    free(A);
    free(B);
    free(C);

    return 0;
}
