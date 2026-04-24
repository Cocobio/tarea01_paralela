#include <iostream>
#include <vector>
std::vector<float> conventional_mult(std::vector<float>& A, std::vector<float>& B, int N) {

    std::vector<float> C(N*N, 0.0f);
    for(int i=0; i<N; i++){ 
        for(int j=0; j<N; j++){
            float sum=0.0f;
            for(int k=0; k<N; k++){
                sum+=(A[i*N+k]*B[k*N+j]);
            }
            C[i*N+j]=sum;
        }
    }

    return C;
}

std::vector<float> strassen_mult(std::vector<float>& A, std::vector<float>& B, int N, int n0=1024) {
    if(N<=n0){
        return conventional_mult(A,B,N);
    }

    std::vector<float> A11((N*N)/4), 
    A12((N*N)/4),
    A21((N*N)/4),
    A22((N*N)/4);


    std::vector<float> B11((N*N)/4),
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

    
    std::vector<float> M1((N*N)/4),
    M2((N*N)/4),M3((N*N)/4),
    M4((N*N)/4),M5((N*N)/4),
    M6((N*N)/4),M7((N*N)/4);

    M1=strassen_mult(M11,M12,N/2);
    M2=strassen_mult(M21,B11,N/2);
    M3=strassen_mult(A11,M32,N/2);
    M4=strassen_mult(A22,M42,N/2);
    M5=strassen_mult(M51,B22,N/2);
    M6=strassen_mult(M61,M62,N/2);
    M7=strassen_mult(M71,M72,N/2);

    std::vector<float> C11((N*N)/4),
    C12((N*N)/4),C21((N*N)/4),
    C22((N*N)/4);

    for(int i=0; i<N/2; i++){
        for(int j=0; j<N/2; j++){
            C11[i*(N/2)+j]=M1[i*(N/2)+j]+M4[i*(N/2)+j]-M5[i*(N/2)+j]+M7[i*(N/2)+j];
            C12[i*(N/2)+j]=M3[i*(N/2)+j]+M5[i*(N/2)+j];
            C21[i*(N/2)+j]=M2[i*(N/2)+j]+M4[i*(N/2)+j];
            C22[i*(N/2)+j]=M1[i*(N/2)+j]-M2[i*(N/2)+j]+M3[i*(N/2)+j]+M6[i*(N/2)+j];           
        }
    }




    std::vector<float> C(N*N);

    for(int i=0; i<N/2; i++){
        for(int j=0; j<N/2; j++){
            C[i*N+j]=C11[i*(N/2)+j];
            C[((N/2)+i)*N+j]=C21[i*(N/2)+j];
            C[i*N+(N/2)+j]=C12[i*(N/2)+j];
            C[((N/2)+i)*N+(N/2)+j]=C22[i*(N/2)+j];       
        }
    }

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

