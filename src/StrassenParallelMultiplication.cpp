#include <vector>


template <class T>
std::vector<T> conventional_mult_parallel(std::vector<T> &A,
                                          std::vector<T> &B,
                                          int N) {
    std::vector<T> C(N * N, 0.0f);

    #pragma omp parallel for collapse(2)
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            T sum = T();
            for (int k = 0; k < N; k++) {
                sum += (A[i * N + k] * B[k * N + j]);
            }
            C[i * N + j] = sum;
        }
    }

    return C;
}


template <class T>
std::vector<T> strassen_mult_parallel(std::vector<T> &A,
                                      std::vector<T> &B,
                                      int N,
                                      int n0 = 2047) {
    if (N <= n0) {
        return conventional_mult_parallel(A, B, N);
    }
  
    std::vector<T> A11((N * N) / 4),
                   A12((N * N) / 4),
                   A21((N * N) / 4),
                   A22((N * N) / 4);

    std::vector<T> B11((N * N) / 4),
                   B12((N * N) / 4),
                   B21((N * N) / 4),
                   B22((N * N) / 4);

    for (int i = 0; i < N / 2; i++) {
        for (int j = 0; j < N / 2; j++) {
            A11[i * (N / 2) + j] = A[i * N + j];
            A12[i * (N / 2) + j] = A[i * N + (N / 2) + j];
            A21[i * (N / 2) + j] = A[((N / 2) + i) * N + j];
            A22[i * (N / 2) + j] = A[((N / 2) + i) * N + (N / 2) + j];
            B11[i * (N / 2) + j] = B[i * N + j];
            B12[i * (N / 2) + j] = B[i * N + (N / 2) + j];
            B21[i * (N / 2) + j] = B[((N / 2) + i) * N + j];
            B22[i * (N / 2) + j] = B[((N / 2) + i) * N + (N / 2) + j];
        }
    }

    std::vector<T> M11((N * N) / 4);
    std::vector<T> M12((N * N) / 4);

    std::vector<T> M21((N * N) / 4);

    std::vector<T> M32((N * N) / 4);

    std::vector<T> M42((N * N) / 4);

    std::vector<T> M51((N * N) / 4);

    std::vector<T> M61((N * N) / 4);
    std::vector<T> M62((N * N) / 4);

    std::vector<T> M71((N * N) / 4);
    std::vector<T> M72((N * N) / 4);

    for (int i = 0; i < N / 2; i++) {
        for (int j = 0; j < N / 2; j++) {
            M11[i * (N / 2) + j] = A11[i * (N / 2) + j] + A22[i * (N / 2) + j];
            M12[i * (N / 2) + j] = B11[i * (N / 2) + j] + B22[i * (N / 2) + j];
            M21[i * (N / 2) + j] = A21[i * (N / 2) + j] + A22[i * (N / 2) + j];
            M32[i * (N / 2) + j] = B12[i * (N / 2) + j] - B22[i * (N / 2) + j];
            M42[i * (N / 2) + j] = B21[i * (N / 2) + j] - B11[i * (N / 2) + j];
            M51[i * (N / 2) + j] = A11[i * (N / 2) + j] + A12[i * (N / 2) + j];
            M61[i * (N / 2) + j] = A21[i * (N / 2) + j] - A11[i * (N / 2) + j];
            M62[i * (N / 2) + j] = B11[i * (N / 2) + j] + B12[i * (N / 2) + j];
            M71[i * (N / 2) + j] = A12[i * (N / 2) + j] - A22[i * (N / 2) + j];
            M72[i * (N / 2) + j] = B21[i * (N / 2) + j] + B22[i * (N / 2) + j];
        }
    }

    std::vector<T> M1((N * N) / 4),
                   M2((N * N) / 4),
                   M3((N * N) / 4),
                   M4((N * N) / 4),
                   M5((N * N) / 4),
                   M6((N * N) / 4),
                   M7((N * N) / 4);

      //auto start = std::chrono::high_resolution_clock::now();
    #pragma omp parallel
    {
        #pragma omp single
        {
            #pragma omp taskgroup
            {
                #pragma omp task shared(M1)
                M1 = strassen_mult_parallel(M11, M12, N / 2);
                #pragma omp task shared(M2)
                M2 = strassen_mult_parallel(M21, B11, N / 2);
                #pragma omp task shared(M3)
                M3 = strassen_mult_parallel(A11, M32, N / 2);
                #pragma omp task shared(M4)
                M4 = strassen_mult_parallel(A22, M42, N / 2);
                #pragma omp task shared(M5)
                M5 = strassen_mult_parallel(M51, B22, N / 2);
                #pragma omp task shared(M6)
                M6 = strassen_mult_parallel(M61, M62, N / 2);
                #pragma omp task shared(M7)
                M7 = strassen_mult_parallel(M71, M72, N / 2);
            }
        }
    }
  
    std::vector<T> C11((N * N) / 4),
                   C12((N * N) / 4),
                   C21((N * N) / 4),
                   C22((N * N) / 4);

    for (int i = 0; i < N / 2; i++) {
        for (int j = 0; j < N / 2; j++) {
            C11[i * (N / 2) + j] = M1[i * (N / 2) + j] + M4[i * (N / 2) + j] -
                                   M5[i * (N / 2) + j] + M7[i * (N / 2) + j];
            C12[i * (N / 2) + j] = M3[i * (N / 2) + j] + M5[i * (N / 2) + j];
            C21[i * (N / 2) + j] = M2[i * (N / 2) + j] + M4[i * (N / 2) + j];
            C22[i * (N / 2) + j] = M1[i * (N / 2) + j] - M2[i * (N / 2) + j] +
                                   M3[i * (N / 2) + j] + M6[i * (N / 2) + j];
        }
    }

    std::vector<T> C(N * N);

    for (int i = 0; i < N / 2; i++) {
        for (int j = 0; j < N / 2; j++) {
            C[i * N + j] = C11[i * (N / 2) + j];
            C[((N / 2) + i) * N + j] = C21[i * (N / 2) + j];
            C[i * N + (N / 2) + j] = C12[i * (N / 2) + j];
            C[((N / 2) + i) * N + (N / 2) + j] = C22[i * (N / 2) + j];
        }
    }

    return C;
}
