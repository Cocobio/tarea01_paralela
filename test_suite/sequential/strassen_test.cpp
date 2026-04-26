#include <cstdlib>
#include <iostream>
#include "../../src/StrassenMultiplication.cpp"
#include "../../src/matrix.cpp"

int main(int argn, char** argv) {
    int N = atoi(argv[1]);
    int base_case = atoi(argv[2]);

    std::vector<float> A(N*N);
    std::vector<float> B(N*N);
    std::vector<float> C;

    // Tecnicamente, un bloque de memoria sin inicializar es random :p

    double time = medir([&]() { C = strassen_mult(A, B, N, base_case); });
    std::cout << "Measure time: " << time << std::endl;

    return 0;
}
