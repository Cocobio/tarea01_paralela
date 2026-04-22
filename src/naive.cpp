#include "matrix.cpp"
#include "SquareMatrix.cpp"


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


template<class T>
vlsi::SquareMatrix<T> naive_multiplication(vlsi::SquareMatrix<T>& A, vlsi::SquareMatrix<T>& B) {
    size_t n = A.dim;
    vlsi::SquareMatrix<T> C(n, T());

    for (int i = 0; i < n; i++)
        for (int k = 0; k < n; k++)
            for (int j = 0; j < n; j++)
                C[i,j] += A[i,k] * B[k,j];

    return C;
}
