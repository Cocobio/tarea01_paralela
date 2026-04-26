#include "SquareMatrix.cpp"
#include <omp.h>

inline void cleanMatrix(float* C, size_t n) {
    memset(C, 0, sizeof(float)*n*n);
}

void tile_multiplication_parallel(float* A, float* B, float* C, size_t n, size_t block_size=16) {
    size_t tile_r_limit = (n+block_size-1)/block_size; // rows of A
    size_t tile_c_limit = (n+block_size-1)/block_size; // cols of B
    size_t tile_n_limit = (n+block_size-1)/block_size; // common dimention

    cleanMatrix(C, n);

    #pragma omp parallel for collapse(2) schedule(static)
    for (size_t tile_i=0; tile_i < tile_r_limit; ++tile_i) {
        for (size_t tile_j=0; tile_j < tile_c_limit; ++tile_j) {
            for (size_t tile_k=0; tile_k < tile_n_limit; ++tile_k) {
                for (size_t i=tile_i*block_size; i<(tile_i+1)*block_size; ++i)
                    for (size_t j=tile_j*block_size; j<(tile_j+1)*block_size; ++j)
                        for (size_t k=tile_k*block_size; k<(tile_k+1)*block_size; ++k)
                            C[i*n+j] += A[i*n+k] * B[k*n+j];
            }
        }
    }
}


template<class T>
vlsi::SquareMatrix<T> tile_multiplication_parallel(vlsi::SquareMatrix<T>& A,
                                                   vlsi::SquareMatrix<T>& B,
                                                   size_t block_size=16) {
    size_t n = A.dim;
    size_t tile_r_limit = (n+block_size-1)/block_size; // rows of A

   // Estos no los usamos, pero serian utilizados para matrices rectangulares
    size_t tile_c_limit = (n+block_size-1)/block_size; // cols of B
    size_t tile_n_limit = (n+block_size-1)/block_size; // common dimention

    vlsi::SquareMatrix<T> C(n, T());

    // Primeros 3 fors, iteran por las tiles/bloques
    for (size_t tile_i=0; tile_i < tile_r_limit; ++tile_i) {
        size_t i_limit = (tile_i+1)*block_size < n ? (tile_i+1)*block_size : n;
        for (size_t tile_j=0; tile_j < tile_c_limit; ++tile_j) {
            size_t j_limit = (tile_j+1)*block_size < n ? (tile_j+1)*block_size : n;
            for (size_t tile_k=0; tile_k < tile_n_limit; ++tile_k) {
                size_t k_limit = (tile_k+1)*block_size < n ? (tile_k+1)*block_size : n;
                // Multiplicacion clasica en los bloques ij ik kj 
                for (size_t i=tile_i*block_size; i<i_limit; ++i)
                    for (size_t j=tile_j*block_size; j<j_limit; ++j)
                        for (size_t k=tile_k*block_size; k<k_limit; ++k)
                            C[i,j] += A[i,k]*B[k,j];
            }
        }
    }

    return C;
}
