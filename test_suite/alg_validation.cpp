#include "../src/NaiveMultiplication.cpp"
#include "../src/TileMultiplication.cpp"
#include "../src/TileParallelMultiplication.cpp"
#include "../src/StrassenMultiplication.cpp"
#include "../src/StrassenParallelMultiplication.cpp"
#include <cstdlib>
#include <iostream>


void validate_sequential(size_t N) {
    std::vector<int> A(N*N);
    std::vector<int> B(N*N);

    for (int i=0; i<N*N; ++i) {
        A[i] = rand()%50;
        B[i] = rand()%50;
    }

    std::vector<int> C(N*N);
    std::vector<int> C1(N*N);
    std::vector<int> C2(N*N);

    naive_mult(A, B, C, N);
    tile_mult(A, B, C1, N);
    strassen_mult(A, B, C2, N);

    std::cout << "naive vs tile" << std::endl;
    for (int i=0; i<N*N; ++i)
        if (C[i] != C1[i]) {
            std::cout << "error!" << i << std::endl;
            std::cout << C[i] << "!=" << C1[i] << std::endl;
        }

    std::cout << "naive vs strassen" << std::endl;
    for (int i=0; i<N*N; ++i)
        if (C[i] != C2[i]) {
            std::cout << "error!" << i << std::endl;
            std::cout << C[i] << "!=" << C2[i] << std::endl;
        }
}


void validate_parallel(size_t N) {
    std::vector<int> A(N*N);
    std::vector<int> B(N*N);

    for (int i=0; i<N*N; ++i) {
        A[i] = rand()%50;
        B[i] = rand()%50;
    }

    std::vector<int> C(N*N);
    std::vector<int> C1(N*N);
    std::vector<int> C2(N*N);

    naive_mult(A, B, C, N);
    tile_mult_parallel(A, B, C1, N);
    strassen_mult_parallel(A, B, C2, N);
    // strassen_hybrid_mult_prallel(A, B, C2, N);

    std::cout << "naive vs tile parallel" << std::endl;
    for (int i=0; i<N*N; ++i)
        if (C[i] != C1[i]) {
            std::cout << "error!" << i << std::endl;
            std::cout << C[i] << "!=" << C1[i] << std::endl;
        }

    std::cout << "naive vs strassen parallel" << std::endl;
    for (int i=0; i<N*N; ++i)
        if (C[i] != C2[i]) {
            std::cout << "error!" << i << std::endl;
            std::cout << C[i] << "!=" << C2[i] << std::endl;
        }
}


int main(int argn, char** argv) {
    srand(67);
    int N = atoi(argv[1]);

    validate_sequential(N);
    validate_parallel(N);

    return 0;
}
