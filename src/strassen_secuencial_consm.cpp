#include <iostream>
#include <vector>
#include "SquareMatrix.cpp"

template<class T>
void conventional_mult(vlsi::SquareMatrix<T>& A,
                       vlsi::SquareMatrix<T>& B,
                       vlsi::SquareMatrix<T>& C,
                       int N) {
    for(int i=0; i<N; i++){ 
        for(int j=0; j<N; j++){
            T sum = T();
            for(int k=0; k<N; k++){
                sum += A[i,k] * B[k,j];
            }
            C[i,j] = sum;
        }
    }
}

template<class T>
void strassen_mult(vlsi::SquareMatrix<T>& A,
                   vlsi::SquareMatrix<T>& B,
                   vlsi::SquareMatrix<T>& C,
                   int N, int n0=1) {
    if(N<=n0){
        conventional_mult(A,B,C,N);
        return;
    }
    
    vlsi::SquareMatrix<T> A11=A.getView(0,0,N/2);
    vlsi::SquareMatrix<T> A21=A.getView(N/2,0,N/2);
    vlsi::SquareMatrix<T> A12=A.getView(0,N/2,N/2);
    vlsi::SquareMatrix<T> A22=A.getView(N/2,N/2,N/2);

    vlsi::SquareMatrix<T> B11=B.getView(0,0,N/2);
    vlsi::SquareMatrix<T> B21=B.getView(N/2,0,N/2);
    vlsi::SquareMatrix<T> B12=B.getView(0,N/2,N/2);
    vlsi::SquareMatrix<T> B22=B.getView(N/2,N/2,N/2);

    vlsi::SquareMatrix<T> M11(N/2),M12(N/2),M21(N/2), M32(N/2), M42(N/2),
                              M51(N/2), M61(N/2), M62(N/2), M71(N/2), M72(N/2);

    for(int i=0; i<N/2; i++){
        for(int j=0; j<N/2; j++){
            M11[i,j]=A11[i,j]+A22[i,j]; //Aqui deberia usar el getView?
            M12[i,j]=B11[i,j]+B22[i,j];
            M21[i,j]=A21[i,j]+A22[i,j];
            M32[i,j]=B12[i,j]-B22[i,j];
            M42[i,j]=B21[i,j]-B11[i,j];
            M51[i,j]=A11[i,j]+A12[i,j];
            M61[i,j]=A21[i,j]-A11[i,j];
            M62[i,j]=B11[i,j]+B12[i,j];
            M71[i,j]=A12[i,j]-A22[i,j];
            M72[i,j]=B21[i,j]+B22[i,j];
            
        }
    }

    vlsi::SquareMatrix<T> M1(N/2);
    vlsi::SquareMatrix<T> M2(N/2);
    vlsi::SquareMatrix<T> M3(N/2);
    vlsi::SquareMatrix<T> M4(N/2);
    vlsi::SquareMatrix<T> M5(N/2);
    vlsi::SquareMatrix<T> M6(N/2);
    vlsi::SquareMatrix<T> M7(N/2);

    strassen_mult(M11,M12,M1,N/2);
    strassen_mult(M21,B11,M2,N/2);
    strassen_mult(A11,M32,M3,N/2);
    strassen_mult(A22,M42,M4,N/2);
    strassen_mult(M51,B22,M5,N/2);
    strassen_mult(M61,M62,M6,N/2);
    strassen_mult(M71,M72,M7,N/2);

    vlsi::SquareMatrix<T> C11=C.getView(0,0,N/2);
    vlsi::SquareMatrix<T> C21=C.getView(N/2,0,N/2);
    vlsi::SquareMatrix<T> C12=C.getView(0,N/2,N/2);
    vlsi::SquareMatrix<T> C22=C.getView(N/2,N/2,N/2);

    for(int i=0; i<N/2; i++){
        for(int j=0; j<N/2; j++){
            C11[i,j]=M1[i,j]+M4[i,j]-M5[i,j]+M7[i,j];
            C12[i,j]=M3[i,j]+M5[i,j];
            C21[i,j]=M2[i,j]+M4[i,j];
            C22[i,j]=M1[i,j]-M2[i,j]+M3[i,j]+M6[i,j];           
        }
    }
}





int main(){

    for(int N=4; N<2048; N=N*2){
        vlsi::SquareMatrix<int> A(N),B(N);
        for(int i=0; i<N;i++){
            for(int j=0; j<N;j++){
                A[i,j]=i;
                B[i,j]=j;
            }
        }

        // for(int i=0; i<N;i++){
        //     for(int j=0; j<N;j++){
        //         std::cout<<A[i,j]<<" ";
        //     }
        //     std::cout<<std::endl;
        // }

        // for(int i=0; i<N;i++){
        //     for(int j=0; j<N;j++){
        //         std::cout<<B[i,j]<<" ";
        //     }
        //     std::cout<<std::endl;
        // }

        vlsi::SquareMatrix<int> Cstrassen(N);
        strassen_mult(A,B,Cstrassen,N,8);
        vlsi::SquareMatrix<int> Cnormal(N);
        conventional_mult(A,B,Cnormal,N);

        std::cout<<"N: "<<N;
        if(Cstrassen==Cnormal){
            std::cout << " OK";
        }
        std::cout <<std::endl;
    }

    return 0;
}

