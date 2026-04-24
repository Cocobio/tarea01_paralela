#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <functional>

using Matrix = std::vector<std::vector<double>>;

Matrix zeros(int n);
Matrix random_matrix(int n);
double medir(std::function<Matrix()> fn);

template <class F>
double medir(F fn);

#endif
