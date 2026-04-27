#include <omp.h>
#include <vector>


template <class T>
void tile_mult_parallel(const std::vector<T>& A,
                        const std::vector<T>& B,
                        std::vector<T>& C,
                        size_t n,
                        size_t block_size=16) {
    for (size_t i=0; i<n*n; i++)
        C[i] = 0;

    #pragma omp parallel for collapse(2) schedule(static)
    for (size_t tile_i=0; tile_i < n; tile_i+=block_size)
        for (size_t tile_j=0; tile_j < n; tile_j+=block_size)
            for (size_t tile_k=0; tile_k < n; tile_k+=block_size)
                for (size_t i=tile_i; i<tile_i+block_size; ++i)
                    for (size_t k=tile_k; k<tile_k+block_size; ++k)
                        for (size_t j=tile_j; j<tile_j+block_size; ++j)
                            C[i*n+j] += A[i*n+k] * B[k*n+j];
}
