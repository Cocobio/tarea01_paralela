#include "strassen_secuencial.cpp"
#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>

int main(){
    std::ofstream timefile("strassenvsconvencionaltimes.txt");

    for (int N=4; N<8192; N*=2)
    {
        timefile<<"N= "<<N<<std::endl;
        std::vector<float> A(N*N),B(N*N),Cstrassen(N*N),Cnormal(N*N);
        for(int i=0; i<N;i++){
            for(int j=0; j<N;j++){
                A[i*N+j]=rand()%10;
                B[i*N+j]=rand()%10;
            }
        }
        auto start = std::chrono::high_resolution_clock::now();
        for(int r=0; r<100; r++){
            Cstrassen=strassen_mult(A,B,N,4);
        }
        auto stop = std::chrono::high_resolution_clock::now();

        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
        timefile<<"Strassen time "<<duration.count()/100<<" us"<<std::endl;
        start = std::chrono::high_resolution_clock::now();
        for(int r=0; r<100; r++){
            Cnormal=conventional_mult(A,B,N);
        }
        stop = std::chrono::high_resolution_clock::now();
        duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
        timefile<<"Conventional time "<<duration.count()/100<<" us"<<std::endl;
        if(Cstrassen!=Cnormal){
            std::cout<<"Error en N= "<<N<<std::endl;

            for(int i=0; i<N;i++){
                for(int j=0; j<N;j++){
                    if(Cstrassen[i*N+j]!=Cnormal[i*N+j]){
                        std::cout<<Cstrassen[i*N+j]<<" "<<Cnormal[i*N+j]<<" ";
                        std::cout<<i<<" "<<j<<std::endl;
                    }
                }
                std::cout<<std::endl;
            }

        }
    }


}