#ifndef AAL05_MATRIXMUL_H_
#define AAL05_MATRIXMUL_H_

#include <cstddef>

void MatrixMul(double **res, double **matrix1, double **matrix2,
               size_t n, size_t m, size_t r);

struct MatrixMul
{
    MatrixMul(double **m1, double **m2, size_t n, size_t m, size_t r);

    double **matrix1;
    double **matrix2;

    size_t n;
    size_t m;
    size_t r;

    double *mulh;
    double *mulv;
    double **res;

    void allocateMemory();
    void calculateMulh();
    void calculateMulv();
    void calculatePart1();
    void calculatePart2();
    void calculateUneven();
};

#endif // AAL05_MATRIXMUL_H_

