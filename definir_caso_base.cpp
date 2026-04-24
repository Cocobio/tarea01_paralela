#include "strassen_secuencial.cpp"
#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>

int main(){
    std::ofstream timefile("strassenvsconvencionaltimes.txt");
    
    for (int N=4; N<512; N*=2)
    {
        timefile<<"N= "<<N<<std::endl;
        std::vector<float> A(N*N),B(N*N),Cstrassen(N*N),Cnormal(N*N);
        
        for(int i=0; i<N;i++){
            for(int j=0; j<N;j++){
                A[i*N+j]=rand();
                B[i*N+j]=rand();
            }
        }
        MatView Av{A,0,0,N},Bv{A,0,0,N};
        auto start = std::chrono::high_resolution_clock::now();
        for(int r=0; r<100; r++){
            Cstrassen=strassen_mult(Av,Bv,N,4);
        }
        auto stop = std::chrono::high_resolution_clock::now();

        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
        timefile<<"Strassen time "<<duration.count()/100<<" us"<<std::endl;
        start = std::chrono::high_resolution_clock::now();
        for(int r=0; r<100; r++){
            Cnormal=conventional_mult(Av,Bv,N);
        }
        stop = std::chrono::high_resolution_clock::now();
        duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
        timefile<<"Conventional time "<<duration.count()/100<<" us"<<std::endl;
    }


}