#include <iostream>
#include <vector>
std::vector<std::vector<float>> conventional_mult(const std::vector<std::vector<float>>& A, const std::vector<std::vector<float>>& B, int N) {

    std::vector<std::vector<float>> C(N, std::vector<float>(N,0.0f));
    for(int i=0; i<N; i++){ 
        for(int j=0; j<N; j++){
            for(int k=0; k<N; k++){
                C[i][j]=C[i][j]+(A[i][k]*B[k][j]);
            }
        }
    }

    return C;
}

std::vector<std::vector<float>> strassen_mult(const std::vector<std::vector<float>>& A, const std::vector<std::vector<float>>& B, int N, int n0=4) {
    if(N<=n0){
        return conventional_mult(A,B,N);
    }

    std::vector<std::vector<float>> A11(N/2, std::vector<float>(N/2, 0.0f)), A12(N/2, std::vector<float>(N/2, 0.0f)), A21(N/2, std::vector<float>(N/2, 0.0f)), A22(N/2, std::vector<float>(N/2, 0.0f));
    std::vector<std::vector<float>> B11(N/2, std::vector<float>(N/2, 0.0f)), B12(N/2, std::vector<float>(N/2, 0.0f)), B21(N/2, std::vector<float>(N/2, 0.0f)), B22(N/2, std::vector<float>(N/2, 0.0f));
    for(int i=0; i<N/2; i++){
        for(int j=0; j<N/2; j++){
            A11[i][j]=A[i][j];
            A12[i][j]=A[i][(N/2)+j];
            A21[i][j]=A[(N/2)+i][j];
            A22[i][j]=A[(N/2)+i][(N/2)+j];
            B11[i][j]=B[i][j];
            B12[i][j]=B[i][(N/2)+j];
            B21[i][j]=B[(N/2)+i][j];
            B22[i][j]=B[(N/2)+i][(N/2)+j];
            
        }
    }

   std::vector<std::vector<float>> M11(N/2, std::vector<float>(N/2, 0.0f));
   std::vector<std::vector<float>> M12(N/2, std::vector<float>(N/2, 0.0f));

   std::vector<std::vector<float>> M21(N/2, std::vector<float>(N/2, 0.0f));

   std::vector<std::vector<float>> M32(N/2, std::vector<float>(N/2, 0.0f));

   std::vector<std::vector<float>> M42(N/2, std::vector<float>(N/2, 0.0f));

   std::vector<std::vector<float>> M51(N/2, std::vector<float>(N/2, 0.0f)) ;

   std::vector<std::vector<float>> M61(N/2, std::vector<float>(N/2, 0.0f));
   std::vector<std::vector<float>> M62(N/2, std::vector<float>(N/2, 0.0f));

   std::vector<std::vector<float>> M71(N/2, std::vector<float>(N/2, 0.0f));
   std::vector<std::vector<float>> M72(N/2, std::vector<float>(N/2, 0.0f));

   for(int i=0; i<N/2; i++){
        for(int j=0; j<N/2; j++){
            M11[i][j]=A11[i][j]+A22[i][j];
            M12[i][j]=B11[i][j]+B22[i][j];
            M21[i][j]=A21[i][j]+A22[i][j];
            M32[i][j]=B12[i][j]-B22[i][j];
            M42[i][j]=B21[i][j]-B11[i][j];
            M51[i][j]=A11[i][j]+A12[i][j];
            M61[i][j]=A21[i][j]-A11[i][j];
            M62[i][j]=B11[i][j]+B12[i][j];
            M71[i][j]=A12[i][j]-A22[i][j];
            M72[i][j]=B21[i][j]+B22[i][j];
            
        }
    }

    std::vector<std::vector<float>> M1(N/2, std::vector<float>(N/2, 0.0f)),
    M2(N/2, std::vector<float>(N/2, 0.0f)),M3(N/2, std::vector<float>(N/2, 0.0f)),
    M4(N/2, std::vector<float>(N/2, 0.0f)),M5(N/2, std::vector<float>(N/2, 0.0f)),
    M6(N/2, std::vector<float>(N/2, 0.0f)),M7(N/2, std::vector<float>(N/2, 0.0f));

    M1=strassen_mult(M11,M12,N/2);
    M2=strassen_mult(M21,B11,N/2);
    M3=strassen_mult(A11,M32,N/2);
    M4=strassen_mult(A22,M42,N/2);
    M5=strassen_mult(M51,B22,N/2);
    M6=strassen_mult(M61,M62,N/2);
    M7=strassen_mult(M71,M72,N/2);

    std::vector<std::vector<float>> C11(N/2, std::vector<float>(N/2, 0.0f)),
    C12(N/2, std::vector<float>(N/2, 0.0f)),C21(N/2, std::vector<float>(N/2, 0.0f)),
    C22(N/2, std::vector<float>(N/2, 0.0f));

    for(int i=0; i<N/2; i++){
        for(int j=0; j<N/2; j++){
            C11[i][j]=M1[i][j]+M4[i][j]-M5[i][j]+M7[i][j];
            C12[i][j]=M3[i][j]+M5[i][j];
            C21[i][j]=M2[i][j]+M4[i][j];
            C22[i][j]=M1[i][j]-M2[i][j]+M3[i][j]+M6[i][j];           
        }
    }

    std::vector<std::vector<float>> C(N, std::vector<float>(N, 0.0f));

    for(int i=0; i<N/2; i++){
        for(int j=0; j<N/2; j++){
            C[i][j]=C11[i][j];
            C[(N/2)+i][j]=C21[i][j];
            C[i][(N/2)+j]=C12[i][j];
            C[(N/2)+i][(N/2)+j]=C22[i][j];       
        }
    }

    return C;
}





int main(){
    int N=8;
    std::vector<std::vector<float>> A(N, std::vector<float>(N,0.0f)),B(N, std::vector<float>(N,0.0f)),Cnormal(N, std::vector<float>(N,0.0f)),Cstrassen(N, std::vector<float>(N,0.0f));
    for(int i=0; i<N;i++){
        for(int j=0; j<N;j++){
            A[i][j]=i*j;
            B[i][j]=i+j;
        }
    }
    Cnormal=conventional_mult(A,B,N);
    Cstrassen=strassen_mult(A,B,N,4);

    for(int i=0; i<N;i++){
        for(int j=0; j<N;j++){
            std::cout<<Cnormal[i][j]<<" ";
        }
        std::cout<<std::endl;
    }

    for(int i=0; i<N;i++){
        for(int j=0; j<N;j++){
            std::cout<<Cstrassen[i][j]<<" ";
        }
        std::cout<<std::endl;
    }

    

    return 0;
}

