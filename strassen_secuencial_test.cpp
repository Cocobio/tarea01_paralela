#include <cstdlib>
#include <iostream>
#include "strassen_secuencial.cpp"

int main(int argn, char** argv) {
    int N = atoi(argv[1]);
    int n0 = atoi(argv[2]);

    float* A = (float*)malloc(N*N*sizeof(float));
    float* B = (float*)malloc(N*N*sizeof(float));
    float* C = (float*)malloc(N*N*sizeof(float));

    
    double time = medir([&]() {
        C=strassen_mult(A, B, N, n0);
    });
    std::cout << "Measure time: " << time << std::endl;

    free(A);
    free(B);
    free(C);

    return 0;
}