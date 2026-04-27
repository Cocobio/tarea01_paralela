#include <cstdlib>
#include <iostream>
#include "../../src/NaiveMultiplication.cpp"
#include "../../src/utils.cpp"

int main(int argn, char** argv) {
    int N = atoi(argv[1]);
    // ignore: argv[2]

    // Tecnicamente, un bloque de memoria sin inicializar es random :p
    std::vector<float> A(N*N);
    std::vector<float> B(N*N);
    std::vector<float> C(N*N);

    double time = medir([&](){ naive_mult(A, B, C, N); });
    std::cout << "Measure time: " << time << std::endl;

    return 0;
}
