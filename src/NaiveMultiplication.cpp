#include <vector>


template<class T>
void naive_mult(const std::vector<T>& A,
                const std::vector<T>& B,
                std::vector<T>& C,
                size_t n) {
    for (int i=0; i<n; ++i)
        for (int j=0; j<n; ++j)
            C[i*n+j] = 0;

    for (int i = 0; i < n; i++)
        for (int k = 0; k < n; k++)
            for (int j = 0; j < n; j++)
                C[i*n+j] += A[i*n+k] * B[k*n+j];
}
