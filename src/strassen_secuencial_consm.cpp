#include <iostream>
#include <vector>
#include "SquareMatrix.cpp"
vlsi::SquareMatrix<float> conventional_mult(vlsi::SquareMatrix<float>& A,vlsi::SquareMatrix<float>& B, int N) {

    vlsi::SquareMatrix<float> C(N);
    
    for(int i=0; i<N; i++){ 
        for(int j=0; j<N; j++){
            float sum = 0.0f;
            for(int k=0; k<N; k++){
                sum += A[i,k] * B[k,j];
                std::cout<<A[i,k]<<"*"<<B[k,j]<<" ";
            }
            std::cout<<std::endl;
            std::cout<<sum<<std::endl;
            C[i,j] = sum;
            std::cout<<C[i,j]<<std::endl;
        }
    }

    return C;
}

// std::vector<std::vector<float>> strassen_mult(const std::vector<std::vector<float>>& A, const std::vector<std::vector<float>>& B, int N, int n0=4) {
//     if(N<=n0){
//         return conventional_mult(A,B,N);
//     }

//     std::vector<std::vector<float>> A11(N/2, std::vector<float>(N/2)), A12(N/2, std::vector<float>(N/2)), A21(N/2, std::vector<float>(N/2)), A22(N/2, std::vector<float>(N/2));
//     std::vector<std::vector<float>> B11(N/2, std::vector<float>(N/2)), B12(N/2, std::vector<float>(N/2)), B21(N/2, std::vector<float>(N/2)), B22(N/2, std::vector<float>(N/2));
//     std::vector<std::vector<float>> M11(N/2, std::vector<float>(N/2));
//    std::vector<std::vector<float>> M12(N/2, std::vector<float>(N/2));

//    std::vector<std::vector<float>> M21(N/2, std::vector<float>(N/2));

//    std::vector<std::vector<float>> M32(N/2, std::vector<float>(N/2));

//    std::vector<std::vector<float>> M42(N/2, std::vector<float>(N/2));

//    std::vector<std::vector<float>> M51(N/2, std::vector<float>(N/2)) ;

//    std::vector<std::vector<float>> M61(N/2, std::vector<float>(N/2));
//    std::vector<std::vector<float>> M62(N/2, std::vector<float>(N/2));

//    std::vector<std::vector<float>> M71(N/2, std::vector<float>(N/2));
//    std::vector<std::vector<float>> M72(N/2, std::vector<float>(N/2));
//     std::vector<std::vector<float>> M1(N/2, std::vector<float>(N/2)),
//     M2(N/2, std::vector<float>(N/2)),M3(N/2, std::vector<float>(N/2)),
//     M4(N/2, std::vector<float>(N/2)),M5(N/2, std::vector<float>(N/2)),
//     M6(N/2, std::vector<float>(N/2)),M7(N/2, std::vector<float>(N/2));
//     std::vector<std::vector<float>> C11(N/2, std::vector<float>(N/2)),
//     C12(N/2, std::vector<float>(N/2)),C21(N/2, std::vector<float>(N/2)),
//     C22(N/2, std::vector<float>(N/2));

//     for(int i=0; i<N/2; i++){
//         for(int j=0; j<N/2; j++){
//             A11[i][j]=A[i][j];
//             A12[i][j]=A[i][(N/2)+j];
//             A21[i][j]=A[(N/2)+i][j];
//             A22[i][j]=A[(N/2)+i][(N/2)+j];
//             B11[i][j]=B[i][j];
//             B12[i][j]=B[i][(N/2)+j];
//             B21[i][j]=B[(N/2)+i][j];
//             B22[i][j]=B[(N/2)+i][(N/2)+j];
            
//         }
//     }

   

//    for(int i=0; i<N/2; i++){
//         for(int j=0; j<N/2; j++){
//             M11[i][j]=A11[i][j]+A22[i][j];
//             M12[i][j]=B11[i][j]+B22[i][j];
//             M21[i][j]=A21[i][j]+A22[i][j];
//             M32[i][j]=B12[i][j]-B22[i][j];
//             M42[i][j]=B21[i][j]-B11[i][j];
//             M51[i][j]=A11[i][j]+A12[i][j];
//             M61[i][j]=A21[i][j]-A11[i][j];
//             M62[i][j]=B11[i][j]+B12[i][j];
//             M71[i][j]=A12[i][j]-A22[i][j];
//             M72[i][j]=B21[i][j]+B22[i][j];
            
//         }
//     }



//     M1=strassen_mult(M11,M12,N/2);
//     M2=strassen_mult(M21,B11,N/2);
//     M3=strassen_mult(A11,M32,N/2);
//     M4=strassen_mult(A22,M42,N/2);
//     M5=strassen_mult(M51,B22,N/2);
//     M6=strassen_mult(M61,M62,N/2);
//     M7=strassen_mult(M71,M72,N/2);

    

//     for(int i=0; i<N/2; i++){
//         for(int j=0; j<N/2; j++){
//             C11[i][j]=M1[i][j]+M4[i][j]-M5[i][j]+M7[i][j];
//             C12[i][j]=M3[i][j]+M5[i][j];
//             C21[i][j]=M2[i][j]+M4[i][j];
//             C22[i][j]=M1[i][j]-M2[i][j]+M3[i][j]+M6[i][j];           
//         }
//     }

//     std::vector<std::vector<float>> C(N, std::vector<float>(N, 0.0f));

//     for(int i=0; i<N/2; i++){
//         for(int j=0; j<N/2; j++){
//             C[i][j]=C11[i][j];
//             C[(N/2)+i][j]=C21[i][j];
//             C[i][(N/2)+j]=C12[i][j];
//             C[(N/2)+i][(N/2)+j]=C22[i][j];       
//         }
//     }

//     return C;
// }





int main(){
    int N=8;
    for(int r=0; r<1; r++){
        vlsi::SquareMatrix<float> A(N),B(N),Cnormal(N),Cstrassen(N);
        for(int i=0; i<N;i++){
            for(int j=0; j<N;j++){
                A[i,j]=1;
                B[i,j]=1;
            }
        }

        for(int i=0; i<N;i++){
            for(int j=0; j<N;j++){
                std::cout<<A[i,j]<<" ";
            }
            std::cout<<std::endl;
        }

        for(int i=0; i<N;i++){
            for(int j=0; j<N;j++){
                std::cout<<B[i,j]<<" ";
            }
            std::cout<<std::endl;
        }


        Cnormal=conventional_mult(A,B,N);
        //Cstrassen=strassen_mult(A,B,N,16);
        for(int i=0; i<N;i++){
            for(int j=0; j<N;j++){
                std::cout<<Cnormal[0,2]<<" ";
            }
            std::cout<<std::endl;
        }
    }
    
    //Cnormal=conventional_mult(A,B,N);
    

    // for(int i=0; i<N;i++){
    //     for(int j=0; j<N;j++){
    //         std::cout<<Cnormal[i][j]<<" ";
    //     }
    //     std::cout<<std::endl;
    // }

    // for(int i=0; i<N;i++){
    //     for(int j=0; j<N;j++){
    //         std::cout<<Cstrassen[i][j]<<" ";
    //     }
    //     std::cout<<std::endl;
    // }

    

    return 0;
}

