#include "matrix.h"
#include <iostream>
#include <vector>
#include <chrono>
#include <cmath>
#include <functional>



Matrix mult_clasica(const Matrix& A, const Matrix& B) 
{
    int n = A.size();
    Matrix C = zeros(n);
    for (int i = 0; i < n; i++)
        for (int k = 0; k < n; k++)
            for (int j = 0; j < n; j++)
                C[i][j] += A[i][k] * B[k][j];
    return C;
}

int main() 
{
    srand(313);
    const std::vector<int> sizes = {256, 512, 1024, 2048, 4096};

    for (int n : sizes) {
        std::cout << "N = " << n << '\n';
        Matrix A = random_matrix(n);
        Matrix B = random_matrix(n);

        std::cout << "Clasica:  " << medir([&]{ return mult_clasica(A, B); }) << " s\n";
    }

}    