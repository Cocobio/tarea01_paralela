#include "matrix.hpp"
#include <iostream>
#include <vector>
#include <chrono>
#include <cmath>
#include <functional>


Matrix zeros(int n) 
{
  return Matrix(n, std::vector<double>(n, 0.0));
}

Matrix random_matrix(int n) 
{
    Matrix A = zeros(n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            A[i][j] = (double)rand() / RAND_MAX;
    return A;
}

double medir(std::function<Matrix()> fn) {
    auto t0 = std::chrono::high_resolution_clock::now();
    fn();
    auto t1 = std::chrono::high_resolution_clock::now();
    return std::chrono::duration<double>(t1 - t0).count(); 
}

template <class F>
double medir(F fn) {
    auto t0 = std::chrono::high_resolution_clock::now();
    fn();
    auto t1 = std::chrono::high_resolution_clock::now();

    return std::chrono::duration<double>(t1 - t0).count(); 
}
