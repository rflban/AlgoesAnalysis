#ifndef AAL02_MATRIXMUL_H_
#define AAL02_MATRIXMUL_H_

#include <cstddef>

void ClassicMul(double **res, double **matrix1, double **matrix2,
                size_t n, size_t m, size_t r);

void WinogradMul(double **res, double **matrix1, double **matrix2,
                 size_t n, size_t m, size_t r);

void OWinogradMul(double **res, double **matrix1, double **matrix2,
                  size_t n, size_t m, size_t r);

#endif // AAL02_MATRIXMUL_H_

