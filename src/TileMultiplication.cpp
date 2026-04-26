#include "SquareMatrix.cpp"

inline void cleanMatrix(float* C, size_t n) {
    memset(C, 0, sizeof(float)*n*n);
}

void tile_multiplication(float* A, float* B, float* C, size_t n, size_t block_size=16) {
    size_t tile_r_limit = (n+block_size-1)/block_size; // rows of A

    cleanMatrix(C, n);

    for (size_t tile_i=0; tile_i < n; tile_i+=block_size) {
        for (size_t tile_j=0; tile_j < n; tile_j+=block_size) {
            for (size_t tile_k=0; tile_k < n; tile_k+=block_size) {
                for (size_t i=tile_i; i<tile_i+block_size; ++i)
                    for (size_t j=tile_j; j<tile_j+block_size; ++j)
                        for (size_t k=tile_k; k<tile_k+block_size; ++k)
                            C[i*n+j] += A[i*n+k] * B[k*n+j];
            }
        }
    }
}
