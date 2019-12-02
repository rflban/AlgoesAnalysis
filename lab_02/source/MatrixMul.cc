#include "MatrixMul.h"

void ClassicMul(double **res, double **matrix1, double **matrix2,
                size_t n, size_t m, size_t r)
{
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < m; j++)
        {
            res[i][j] = 0;

            for (size_t k = 0; k < r; k++)
            {
                res[i][j] = res[i][j] + matrix1[i][k] * matrix2[k][j];
            }
        }
    }
}

void WinogradMul(double **res, double **matrix1, double **matrix2,
                 size_t n, size_t m, size_t r)
{
    double *mulh = new double[n]();
    double *mulv = new double[m]();

    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < r / 2; j++)
        {
            mulh[i] = mulh[i] + matrix1[i][2 * j] * matrix1[i][2 * j + 1];
        }
    }

    for (size_t j = 0; j < m; j++)
    {
        for (size_t i = 0; i < r / 2; i++)
        {
            mulv[j] = mulv[j] + matrix2[2 * i][j] * matrix2[2 * i + 1][j];
        }
    }

    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < m; j++)
        {
            res[i][j] = -(mulh[i] + mulv[j]);

            for (size_t k = 0; k < r / 2; k++)
            {
                res[i][j] = res[i][j] +
                            (matrix1[i][2 * k] + matrix2[2 * k + 1][j]) *
                            (matrix1[i][2 * k + 1] + matrix2[2 * k][j]);
            }
        }
    }

    if (r % 2 == 1)
    {
        for (size_t i = 0; i < n; i++)
            for (size_t j = 0; j < m; j++)
                res[i][j] = res[i][j] + matrix1[i][r - 1] * matrix2[r - 1][j];
    }

    delete[] mulh;
    delete[] mulv;
}

// a = a + ... (->) a += ...
// a / 2 (->) a >> 1
// a * 2 (->) a << 1
// a % 2 == 1 (->) a & 1
// cycle (expression) ... (->) bool b = expression; cycle (b) ...
// cycle { matrix[i][j] = ... } (->) temp; cycle { temp = ... }; matrix[i][j] = temp
void OWinogradMul(double **res, double **matrix1, double **matrix2,
                  size_t n, size_t m, size_t r)
{
    double temp;

    double *mulh = new double[n]();
    double *mulv = new double[m]();

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

