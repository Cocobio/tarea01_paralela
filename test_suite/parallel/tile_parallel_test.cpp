#include <cstdlib>
#include <iostream>
#include "../../src/TileParallelMultiplication.cpp"
#include "../../src/utils.cpp"

int main(int argn, char** argv) {
    int N = atoi(argv[1]);
    int tile = atoi(argv[2]);

    // Tecnicamente, un bloque de memoria sin inicializar es random :p
    std::vector<float> A(N*N);
    std::vector<float> B(N*N);
    std::vector<float> C(N*N);

    double time = medir([&](){ tile_mult_parallel(A, B, C, N, tile); });
    std::cout << "Measure time: " << time << std::endl;

    return 0;
}
