#ifndef AAL04_MATRIXMUL_H_
#define AAL04_MATRIXMUL_H_

#include <cstddef>

void MatrixMul(double **res, double **matrix1, double **matrix2,
               size_t n, size_t m, size_t r,
               size_t start, size_t end);

#endif // AAL04_MATRIXMUL_H_

