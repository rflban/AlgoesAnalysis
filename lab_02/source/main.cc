#include <iostream>
#include <chrono>

#include <random>
#include <ctime>

#include "Utility.h"
#include "MatrixMul.h"

using namespace std;

using NanoSecs = std::chrono::duration<unsigned long long, std::nano>;
using TimePoint = std::chrono::steady_clock::time_point;

inline static TimePoint tick()
{
    return std::chrono::steady_clock::now();
}

inline static NanoSecs toNanoSecs(std::chrono::steady_clock::duration dur)
{
    return std::chrono::duration_cast<NanoSecs>(dur);
}

double **readMatrix(size_t n, size_t m);
void printMatrix(double **matrix, size_t n, size_t m);

void timeTest(void (*matrixMul)(double**, double**, double**, size_t, size_t, size_t),
              size_t first, size_t last, size_t step, size_t repeats);

int main(int argc, char **argv)
{
    bool doTest = false;
    TimePoint begin;
    TimePoint end;

    size_t n1, m1;
    size_t n2, m2;

    void (*matrixMul)(double**, double**, double**, size_t, size_t, size_t) = &ClassicMul;

    for (int idx = 1; idx < argc; idx++)
    {
        if (argv[idx][0] == '1')
        {
            matrixMul = &ClassicMul;
        }
        else if (argv[idx][0] == '2')
        {
            matrixMul = &WinogradMul;
        }
        else if (argv[idx][0] == '3')
        {
            matrixMul = &OWinogradMul;
        }
        else if (argv[idx][0] == 't')
        {
            doTest = true;
        }
        else if (argv[idx][0] == 'T')
        {
            doTest = false;
        }
    }

    if (doTest)
    {
        timeTest(matrixMul, 0, 1000, 100, 5);
        return 0;
    }

    cin >> n1 >> m1;
    cin >> n2 >> m2;

    if (m1 != n2)
    {
        return 1;
    }

    double **matrix1 = readMatrix(n1, m1);
    double **matrix2 = readMatrix(n2, m2);
    double **res = Util::createMatrix<double>(n1, m2);

    begin = tick();
    matrixMul(res, matrix1, matrix2, n1, m2, n2);
    end = tick();
    printMatrix(res, n1, m2);

    delete[] matrix1;
    delete[] matrix2;
    delete[] res;

    cout << toNanoSecs(end - begin).count() << '\n';

    return 0;
}

void printMatrix(double **matrix, size_t n, size_t m)
{
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < m; j++)
        {
            printf("%6.3lf ", matrix[i][j]);
        }

        printf("\n");
    }
}

double **readMatrix(size_t n, size_t m)
{
    int rc;
    double temp;
    double **matrix = Util::createMatrix<double>(n, m);

    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < m; j++)
        {
            rc = scanf("%lf", &temp);

            if (rc != 1)
            {
                delete[] matrix;
                return nullptr;
            }

            matrix[i][j] = temp;
        }
    }

    return matrix;
}

void randomFill(double **matrix, size_t n, size_t m)
{
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < m; j++)
        {
            matrix[i][j] = (double)rand() / RAND_MAX;
        }
    }
}

void timeTest(void (*matrixMul)(double**, double**, double**, size_t, size_t, size_t),
              size_t first, size_t last, size_t step, size_t repeats)
{
    if (first > last + 1 || last == 0 || step == 0 || repeats == 0)
    {
        return;
    }

    srand(time(0));

    size_t current = first;
    double **matrix1 = Util::createMatrix<double>(last, last);
    double **matrix2 = Util::createMatrix<double>(last, last);
    double **res = Util::createMatrix<double>(last, last);

    TimePoint begin;
    TimePoint end;
    unsigned long long delta;

    while (current <= last)
    {
        delta = 0;
        randomFill(matrix1, current, current);
        randomFill(matrix2, current, current);

        for (size_t i = 0; i < repeats; i++)
        {
            begin = tick();
            matrixMul(res, matrix1, matrix2, current, current, current);
            end = tick();

            delta += toNanoSecs(end - begin).count();
        }

        delta /= repeats;

        cout << current << " " << delta << '\n';

        current += step;
    }

    delete[] matrix1;
    delete[] matrix2;
    delete[] res;
}

