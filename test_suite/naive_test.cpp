#include <cstdlib>
#include <iostream>
#include "../src/naive.cpp"
#include "../src/matrix.hpp"

int main(int argn, char** argv) {
    int N = atoi(argv[1]);
    // ignore: argv[2]

    Matrix A = random_matrix(N);
    Matrix B = random_matrix(N);

    double time = medir([&]{ return mult_clasica(A, B); });
    std::cout << "Measure time: " << time << std::endl;

    return 0;
}
