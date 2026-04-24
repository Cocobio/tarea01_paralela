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
                //std::cout<<A[i,k]<<"*"<<B[k,j]<<" ";
            }
            //std::cout<<std::endl;
            //std::cout<<sum<<std::endl;
            C[i,j] = sum;
            //std::cout<<C[i,j]<<std::endl;
        }
    }

    return C;
}

vlsi::SquareMatrix<float> strassen_mult(vlsi::SquareMatrix<float>& A, vlsi::SquareMatrix<float>& B, int N, int n0=4) {
    if(N<=n0){
        return conventional_mult(A,B,N);
    }


    
    vlsi::SquareMatrix<float> A11=A.getView(0,0,N/2);
    vlsi::SquareMatrix<float> A12=A.getView(N/2,0,N/2);
    vlsi::SquareMatrix<float> A21=A.getView(N/2,0,N/2);
    vlsi::SquareMatrix<float> A22=A.getView(N/2,N/2,N/2);

    vlsi::SquareMatrix<float> B11=B.getView(0,0,N/2);
    vlsi::SquareMatrix<float> B12=B.getView(N/2,0,N/2);
    vlsi::SquareMatrix<float> B21=B.getView(N/2,0,N/2);
    vlsi::SquareMatrix<float> B22=B.getView(N/2,N/2,N/2);

    vlsi::SquareMatrix<float> M11(N,0),M12(N,1),M21(N,2), M32(N,3), M42(N,4), M51(N,5), M61(N,6), M62(N,7), M71(N,8), M72(N,9);

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






   

   



    vlsi::SquareMatrix<float> M1=strassen_mult(M11,M12,N/2);
    vlsi::SquareMatrix<float> M2=strassen_mult(M21,B11,N/2);
    vlsi::SquareMatrix<float> M3=strassen_mult(A11,M32,N/2);
    vlsi::SquareMatrix<float> M4=strassen_mult(A22,M42,N/2);
    vlsi::SquareMatrix<float> M5=strassen_mult(M51,B22,N/2);
    vlsi::SquareMatrix<float> M6=strassen_mult(M61,M62,N/2);
    vlsi::SquareMatrix<float> M7=strassen_mult(M71,M72,N/2);

    vlsi::SquareMatrix<float> C(N,10);

    vlsi::SquareMatrix<float> C11=C.getView(0,0,N/2);
    vlsi::SquareMatrix<float> C12=C.getView(N/2,0,N/2);
    vlsi::SquareMatrix<float> C21=C.getView(N/2,0,N/2);
    vlsi::SquareMatrix<float> C22=C.getView(N/2,N/2,N/2);

    

    for(int i=0; i<N/2; i++){
        for(int j=0; j<N/2; j++){
            C11[i,j]=M1[i,j]+M4[i,j]-M5[i,j]+M7[i,j];
            C12[i,j]=M3[i,j]+M5[i,j];
            C21[i,j]=M2[i,j]+M4[i,j];
            C22[i,j]=M1[i,j]-M2[i,j]+M3[i,j]+M6[i,j];           
        }
    }

    

    // for(int i=0; i<N/2; i++){
    //     for(int j=0; j<N/2; j++){
    //         C[i][j]=C11[i][j];
    //         C[(N/2)+i][j]=C21[i][j];
    //         C[i][(N/2)+j]=C12[i][j];
    //         C[(N/2)+i][(N/2)+j]=C22[i][j];       
    //     }
    // }

    return C;
}





int main(){

    for(int N=4; N<2048; N=N*2){
        vlsi::SquareMatrix<float> A(N),B(N);
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

        vlsi::SquareMatrix<float> Cstrassen=strassen_mult(A,B,N,8);
        vlsi::SquareMatrix<float> Cnormal=conventional_mult(A,B,N);
        //Cstrassen=strassen_mult(A,B,N,16);
        // for(int i=0; i<N;i++){
        //     for(int j=0; j<N;j++){
        //         std::cout<<Cstrassen[i,j]<<" ";
        //     }
        //     std::cout<<std::endl;
        // }
        if(Cstrassen==Cnormal){
            std::cout<<"N: "<<N<<" OK"<<std::endl;
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

