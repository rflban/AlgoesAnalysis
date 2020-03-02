#include "MatrixMul.h"
#include "Utility.h"

void MatrixMul(double **res, double **matrix1, double **matrix2,
               size_t n, size_t m, size_t r)
{
    double temp;

    double *mulh = new double[n];
    double *mulv = new double[m];

    double r_div_2 = r >> 1;

    for (size_t i = 0; i < n; i++)
    {
        temp = 0;

        for (size_t j = 0; j < r_div_2; j++)
        {
            temp += matrix1[i][j << 1] * matrix1[i][(j << 1) + 1];
        }

        mulh[i] = temp;
    }

    for (size_t j = 0; j < m; j++)
    {
        temp = 0;

        for (size_t i = 0; i < r_div_2; i++)
        {
            temp += matrix2[i << 1][j] * matrix2[(i << 1) + 1][j];
        }

        mulv[j] = temp;
    }

    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < m; j++)
        {
            temp = -(mulh[i] + mulv[j]);

            for (size_t k = 0; k < r_div_2; k++)
            {
                temp += (matrix1[i][k << 1] + matrix2[(k << 1) + 1][j]) *
                        (matrix1[i][(k << 1) + 1] + matrix2[k << 1][j]);
            }

            res[i][j] = temp;
        }
    }

    if (r & 1)
    {
        for (size_t i = 0; i < n; i++)
            for (size_t j = 0; j < m; j++)
                res[i][j] += matrix1[i][r - 1] * matrix2[r - 1][j];
    }

    delete[] mulh;
    delete[] mulv;
}

MatrixMul::MatrixMul(double **m1, double **m2,
                     size_t n, size_t m, size_t r) :
    matrix1(m1), matrix2(m2), n(n), m(m), r(r),
    mulh(nullptr), mulv(nullptr), res(nullptr)
{
}

void MatrixMul::allocateMemory()
{
    mulh = new double[n];
    mulv = new double[m];

    res = Util::createMatrix<double>(n, m);
}

void MatrixMul::calculateMulh()
{
    double temp;
    size_t r_div_2 = r >> 1;

    for (size_t i = 0; i < n; i++)
    {
        temp = 0;

        for (size_t j = 0; j < r_div_2; j++)
        {
            temp += matrix1[i][j << 1] * matrix1[i][(j << 1) + 1];
        }

        mulh[i] = temp;
    }
}

void MatrixMul::calculateMulv()
{
    double temp;
    size_t r_div_2 = r >> 1;

    for (size_t j = 0; j < m; j++)
    {
        temp = 0;

        for (size_t i = 0; i < r_div_2; i++)
        {
            temp += matrix2[i << 1][j] * matrix2[(i << 1) + 1][j];
        }

        mulv[j] = temp;
    }
}

void MatrixMul::calculatePart1()
{
    double temp;

    size_t r_div_2 = r >> 1;
    size_t n_div_2 = n >> 1;

    for (size_t i = 0; i < n_div_2; i++)
    {
        for (size_t j = 0; j < m; j++)
        {
            temp = -(mulh[i] + mulv[j]);

            for (size_t k = 0; k < r_div_2; k++)
            {
                temp += (matrix1[i][k << 1] + matrix2[(k << 1) + 1][j]) *
                        (matrix1[i][(k << 1) + 1] + matrix2[k << 1][j]);
            }

            res[i][j] = temp;
        }
    }
}

void MatrixMul::calculatePart2()
{
    double temp;

    size_t r_div_2 = r >> 1;
    size_t n_div_2 = n >> 1;

    for (size_t i = n_div_2; i < n; i++)
    {
        for (size_t j = 0; j < m; j++)
        {
            temp = -(mulh[i] + mulv[j]);

            for (size_t k = 0; k < r_div_2; k++)
            {
                temp += (matrix1[i][k << 1] + matrix2[(k << 1) + 1][j]) *
                        (matrix1[i][(k << 1) + 1] + matrix2[k << 1][j]);
            }

            res[i][j] = temp;
        }
    }
}

void MatrixMul::calculateUneven()
{
    if (r & 1)
    {
        for (size_t i = 0; i < n; i++)
            for (size_t j = 0; j < m; j++)
                res[i][j] += matrix1[i][r - 1] * matrix2[r - 1][j];
    }

    delete[] mulh;
    delete[] mulv;

    mulh = nullptr;
    mulv = nullptr;
}

