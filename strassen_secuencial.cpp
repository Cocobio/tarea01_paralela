#include <iostream>
#include <vector>

struct MatView {
    const std::vector<float>& data;
    int row0, col0;
    int stride;

    float operator()(int i, int j) const {
        return data[(row0 + i) * stride + (col0 + j)];
    }
};

struct MatRef {
    std::vector<float>& data;
    int row0, col0;
    int stride;

    float& operator()(int i, int j) {
        return data[(row0 + i) * stride + (col0 + j)];
    }
};


std::vector<float> conventional_mult(MatView A, MatView B, int N) {

    std::vector<float> C(N*N, 0.0f);
    for(int i=0; i<N; i++){ 
        for(int j=0; j<N; j++){
            float sum=0.0f;
            for(int k=0; k<N; k++){
                sum+=(A(i,k)*B(k,j));
            }
            C[i*N+j]=sum;
        }
    }

    return C;
}

std::vector<float> strassen_mult(MatView A, MatView B, int N, int n0=4) {
    if(N<=n0){
        return conventional_mult(A,B,N);
    }

    int h = N / 2;

    MatView A11{A.data, A.row0,     A.col0,     A.stride};
    MatView A12{A.data, A.row0,     A.col0 + h, A.stride};
    MatView A21{A.data, A.row0 + h, A.col0,     A.stride};
    MatView A22{A.data, A.row0 + h, A.col0 + h, A.stride};

    MatView B11{B.data, B.row0,     B.col0,     B.stride};
    MatView B12{B.data, B.row0,     B.col0 + h, B.stride};
    MatView B21{B.data, B.row0 + h, B.col0,     B.stride};
    MatView B22{B.data, B.row0 + h, B.col0 + h, B.stride};


    // for(int i=0; i<N/2; i++){
    //     for(int j=0; j<N/2; j++){
    //         A11[i*(N/2)+j]=A[i*N+j];
    //         A12[i*(N/2)+j]=A[i*N+(N/2)+j];
    //         A21[i*(N/2)+j]=A[((N/2)+i)*N+j];
    //         A22[i*(N/2)+j]=A[((N/2)+i)*N+(N/2)+j];
    //         B11[i*(N/2)+j]=B[i*N+j];
    //         B12[i*(N/2)+j]=B[i*N+(N/2)+j];
    //         B21[i*(N/2)+j]=B[((N/2)+i)*N+j];
    //         B22[i*(N/2)+j]=B[((N/2)+i)*N+(N/2)+j];
            
    //     }
    // }

   std::vector<float> M11((N*N)/4);
   std::vector<float> M12((N*N)/4);

   std::vector<float> M21((N*N)/4);

   std::vector<float> M32((N*N)/4);

   std::vector<float> M42((N*N)/4);

   std::vector<float> M51((N*N)/4) ;

   std::vector<float> M61((N*N)/4);
   std::vector<float> M62((N*N)/4);

   std::vector<float> M71((N*N)/4);
   std::vector<float> M72((N*N)/4);

   for(int i=0; i<N/2; i++){
        for(int j=0; j<N/2; j++){
            M11[i*(N/2)+j]=A11(i,j)+A22(i,j);
            M12[i*(N/2)+j]=B11(i,j)+B22(i,j);
            M21[i*(N/2)+j]=A21(i,j)+A22(i,j);
            M32[i*(N/2)+j]=B12(i,j)-B22(i,j);
            M42[i*(N/2)+j]=B21(i,j)-B11(i,j);
            M51[i*(N/2)+j]=A11(i,j)+A12(i,j);
            M61[i*(N/2)+j]=A21(i,j)-A11(i,j);
            M62[i*(N/2)+j]=B11(i,j)+B12(i,j);
            M71[i*(N/2)+j]=A12(i,j)-A22(i,j);
            M72[i*(N/2)+j]=B21(i,j)+B22(i,j);
            
        }
    }
    
    MatView M11v{M11, 0, 0, h};
    MatView M12v{M12, 0, 0, h};
    MatView M21v{M21, 0, 0, h};
    MatView M32v{M32, 0, 0, h};
    MatView M42v{M42, 0, 0, h};
    MatView M51v{M51, 0, 0, h};
    MatView M61v{M61, 0, 0, h};
    MatView M62v{M62, 0, 0, h};
    MatView M71v{M71, 0, 0, h};
    MatView M72v{M72, 0, 0, h};


    std::vector<float> M1((N*N)/4),
    M2((N*N)/4),M3((N*N)/4),
    M4((N*N)/4),M5((N*N)/4),
    M6((N*N)/4),M7((N*N)/4);

    M1=strassen_mult(M11v,M12v,N/2);
    M2=strassen_mult(M21v,B11,N/2);
    M3=strassen_mult(A11,M32v,N/2);
    M4=strassen_mult(A22,M42v,N/2);
    M5=strassen_mult(M51v,B22,N/2);
    M6=strassen_mult(M61v,M62v,N/2);
    M7=strassen_mult(M71v,M72v,N/2);

    std::vector<float> C(N*N);


    MatRef C11{C, 0, 0, N};
    MatRef C12{C, 0, h, N};
    MatRef C21{C, h, 0, N};
    MatRef C22{C, h, h, N};

    for(int i=0; i<N/2; i++){
        for(int j=0; j<N/2; j++){
            C11(i,j)=M1[i*(N/2)+j]+M4[i*(N/2)+j]-M5[i*(N/2)+j]+M7[i*(N/2)+j];
            C12(i,j)=M3[i*(N/2)+j]+M5[i*(N/2)+j];
            C21(i,j)=M2[i*(N/2)+j]+M4[i*(N/2)+j];
            C22(i,j)=M1[i*(N/2)+j]-M2[i*(N/2)+j]+M3[i*(N/2)+j]+M6[i*(N/2)+j];           
        }
    }

   

    // for(int i=0; i<N/2; i++){
    //     for(int j=0; j<N/2; j++){
    //         C[i*N+j]=C11[i*(N/2)+j];
    //         C[((N/2)+i)*N+j]=C21[i*(N/2)+j];
    //         C[i+(N/2)+j]=C12[i*(N/2)+j];
    //         C[((N/2)+i)*N+(N/2)+j]=C22[i*(N/2)+j];       
    //     }
    // }

    return C;
}





// int main(){
//     int N=8;
//     std::vector<float> A(N, std::vector<float>(N,0.0f)),B(N, std::vector<float>(N,0.0f)),Cnormal(N, std::vector<float>(N,0.0f)),Cstrassen(N, std::vector<float>(N,0.0f));
//     for(int i=0; i<N;i++){
//         for(int j=0; j<N;j++){
//             A[i*(N/2)+j]=i*j;
//             B[i*(N/2)+j]=i+j;
//         }
//     }
//     Cnormal=conventional_mult(A,B,N);
//     Cstrassen=strassen_mult(A,B,N,4);

//     for(int i=0; i<N;i++){
//         for(int j=0; j<N;j++){
//             std::cout<<Cnormal[i*(N/2)+j]<<" ";
//         }
//         std::cout<<std::endl;
//     }

//     for(int i=0; i<N;i++){
//         for(int j=0; j<N;j++){
//             std::cout<<Cstrassen[i*(N/2)+j]<<" ";
//         }
//         std::cout<<std::endl;
//     }

    

//     return 0;
// }

