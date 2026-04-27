#include <cstdlib>
#include <iostream>
#include "../../src/TileMultiplication.cpp"
#include "../../src/matrix.cpp"

int main(int argn, char** argv) {
    int N = atoi(argv[1]);
    int tile = atoi(argv[2]);

    // Tecnicamente, un bloque de memoria sin inicializar es random :p
    std::vector<float> A(N*N);
    std::vector<float> B(N*N);
    std::vector<float> C(N*N);

    auto start = std::chrono::high_resolution_clock::now();
    tile_mult(A, B, C, N, tile);
    auto end = std::chrono::high_resolution_clock::now();
    auto time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    std::cout << "Measure time: " << time/1000.0 << std::endl;

    return 0;
}
