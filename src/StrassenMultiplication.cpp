#include <vector>


template <class T>
inline void conventional_mult(const std::vector<T>& A,
                              const std::vector<T>& B,
                              std::vector<T>& C,
                              size_t N) {
    for (int i=0; i<N; ++i)
        for (int j=0; j<N; ++j)
            C[i*N+j] = T();

    for(int i=0; i<N; i++)
        for(int k=0; k<N; k++)
            for(int j=0; j<N; j++)
                C[i*N+j] += A[i*N+k]*B[k*N+j];
}


template <class T>
void strassen_mult(const std::vector<T>& A,
                   const std::vector<T>& B,
                   std::vector<T>& C,
                   size_t N,
                   int n0=64) {
    if(N<=n0){
        return conventional_mult(A,B,C,N);
    }

    std::vector<T> A11((N*N)/4), 
                   A12((N*N)/4),
                   A21((N*N)/4),
                   A22((N*N)/4);

    std::vector<T> B11((N*N)/4),
                   B12((N*N)/4),
                   B21((N*N)/4),
                   B22((N*N)/4);

    for(int i=0; i<N/2; i++){
        for(int j=0; j<N/2; j++){
            A11[i*(N/2)+j]=A[i*N+j];
            A12[i*(N/2)+j]=A[i*N+(N/2)+j];
            A21[i*(N/2)+j]=A[((N/2)+i)*N+j];
            A22[i*(N/2)+j]=A[((N/2)+i)*N+(N/2)+j];
            B11[i*(N/2)+j]=B[i*N+j];
            B12[i*(N/2)+j]=B[i*N+(N/2)+j];
            B21[i*(N/2)+j]=B[((N/2)+i)*N+j];
            B22[i*(N/2)+j]=B[((N/2)+i)*N+(N/2)+j];
        }
    }

    std::vector<T> M11((N*N)/4);
    std::vector<T> M12((N*N)/4);

    std::vector<T> M21((N*N)/4);

    std::vector<T> M32((N*N)/4);

    std::vector<T> M42((N*N)/4);

    std::vector<T> M51((N*N)/4) ;

    std::vector<T> M61((N*N)/4);
    std::vector<T> M62((N*N)/4);

    std::vector<T> M71((N*N)/4);
    std::vector<T> M72((N*N)/4);

    for(int i=0; i<N/2; i++){
        for(int j=0; j<N/2; j++){
            M11[i*(N/2)+j]=A11[i*(N/2)+j]+A22[i*(N/2)+j];
            M12[i*(N/2)+j]=B11[i*(N/2)+j]+B22[i*(N/2)+j];
            M21[i*(N/2)+j]=A21[i*(N/2)+j]+A22[i*(N/2)+j];
            M32[i*(N/2)+j]=B12[i*(N/2)+j]-B22[i*(N/2)+j];
            M42[i*(N/2)+j]=B21[i*(N/2)+j]-B11[i*(N/2)+j];
            M51[i*(N/2)+j]=A11[i*(N/2)+j]+A12[i*(N/2)+j];
            M61[i*(N/2)+j]=A21[i*(N/2)+j]-A11[i*(N/2)+j];
            M62[i*(N/2)+j]=B11[i*(N/2)+j]+B12[i*(N/2)+j];
            M71[i*(N/2)+j]=A12[i*(N/2)+j]-A22[i*(N/2)+j];
            M72[i*(N/2)+j]=B21[i*(N/2)+j]+B22[i*(N/2)+j];
        }
    }

    std::vector<T> M1((N*N)/4),
                   M2((N*N)/4),
                   M3((N*N)/4),
                   M4((N*N)/4),
                   M5((N*N)/4),
                   M6((N*N)/4),
                   M7((N*N)/4);

    strassen_mult(M11, M12, M1, N/2);
    strassen_mult(M21, B11, M2, N/2);
    strassen_mult(A11, M32, M3, N/2);
    strassen_mult(A22, M42, M4, N/2);
    strassen_mult(M51, B22, M5, N/2);
    strassen_mult(M61, M62, M6, N/2);
    strassen_mult(M71, M72, M7, N/2);

    std::vector<T> C11((N*N)/4),
                   C12((N*N)/4),
                   C21((N*N)/4),
                   C22((N*N)/4);

    for(int i=0; i<N/2; i++){
        for(int j=0; j<N/2; j++){
            C[i*N+j]          = M1[i*(N/2)+j]+M4[i*(N/2)+j]-M5[i*(N/2)+j]+M7[i*(N/2)+j];
            C[i*N+j+N/2]      = M3[i*(N/2)+j]+M5[i*(N/2)+j];
            C[(i+N/2)*N+j]    = M2[i*(N/2)+j]+M4[i*(N/2)+j];
            C[(i+N/2)*N+j+N/2]= M1[i*(N/2)+j]-M2[i*(N/2)+j]+M3[i*(N/2)+j]+M6[i*(N/2)+j];           
        }
    }
}
