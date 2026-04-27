#include <cstdlib>
#include <iostream>
#include "../../src/StrassenParallelMultiplication.cpp"
#include "../../src/matrix.cpp"

int main(int argn, char** argv) {
    int N = atoi(argv[1]);
    int n0 = atoi(argv[2]);

    // Tecnicamente, un bloque de memoria sin inicializar es random :p
    std::vector<float> A(N*N);
    std::vector<float> B(N*N);
    std::vector<float> C(N*N);
    
    double time = medir([&]() { strassen_mult_parallel(A, B, C, N, n0); });
    std::cout << "Measure time: " << time << std::endl;

    return 0;
}
