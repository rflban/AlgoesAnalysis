#include <iostream>
#include <chrono>
#include <random>
#include <ctime>

#include <thread>
#include <vector>

#include "Utility.h"
#include "MatrixMul.h"
#include "MatrixDescriptor.h"

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

void timeTest(int threadsQty, bool isEven);

class Multythread
{
public:
    static
    void MatrixMul(MatrixDescriptor &res, MatrixDescriptor &md1, MatrixDescriptor &md2,
                   size_t start, size_t end)
    {
        ::MatrixMul(res.data, md1.data, md2.data, md1.n, md2.m, md1.m, start, end);
    }
};

int main(int argc, char **argv)
{
    bool doTest = false;
    bool isEven = true;

    for (int i = 1; i < argc; i++)
    {
        if (argv[i][0] == 'e')
        {
            doTest = true;
            isEven = true;
        }
        else if (argv[i][0] == 'u')
        {
            doTest = true;
            isEven = false;
        }
    }

    int n;
    int threadsQty;

    std::cin >> threadsQty;

    if (doTest)
    {
        timeTest(threadsQty, isEven);
        exit(0);
    }

    std::thread *threads = new std::thread[threadsQty];

    std::cin >> n;

    double **matrix1 = readMatrix(n, n);
    double **matrix2 = readMatrix(n, n);

    if (matrix1 == nullptr || matrix2 == nullptr)
    {
        exit(1);
    }

    size_t step = n / threadsQty;
    size_t start = 0;
    size_t end = start + step + n % threadsQty;

    double **res = Util::createMatrix<double>(n, n);

    MatrixDescriptor md1 = { n, n, matrix1 };
    MatrixDescriptor md2 = { n, n, matrix2 };
    MatrixDescriptor md3 = { n, n, res };

    for (int i = 0; i < threadsQty; i++)
    {
        threads[i] = std::thread(Multythread::MatrixMul, std::ref(md3), std::ref(md1), std::ref(md2), start, end);

        start = end;
        end += step;
    }

    for (int i = 0; i < threadsQty; i++)
    {
        threads[i].join();
    }

    printMatrix(matrix1, n, n);
    printf("\n");
    printMatrix(matrix2, n, n);
    printf("\n");
    printMatrix(res, n, n);

    delete[] threads;
    delete[] matrix1;
    delete[] matrix2;
    delete[] res;

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

void timeTest(int threadsQty, bool isEven)
{
    TimePoint t1, t2;
    std::chrono::steady_clock::rep time_sum = 0;

    int n = 100;
    int h = 100;
    int maxN = 1000;
    int repeatsQty = 5;

    if(!isEven)
    {
        n++;
        maxN++;
    }

    std::thread *threads = new std::thread[threadsQty];

    std::cout << "len,time" << '\n';

    for (; n <= maxN; n += h)
    {
        MatrixDescriptor md1 = { n, n, Util::createMatrix<double>(n, n) };
        MatrixDescriptor md2 = { n, n, Util::createMatrix<double>(n, n) };
        MatrixDescriptor md3 = { n, n, Util::createMatrix<double>(n, n) };

        randomFill(md1.data, n, n);
        randomFill(md2.data, n, n);

        time_sum = 0;

        for (int j = 0; j < repeatsQty; j++)
        {
            size_t step = n / threadsQty;
            size_t start = 0;
            size_t end = start + step + n % threadsQty;

            for (int i = 0; i < threadsQty; i++)
            {
                threads[i] = std::thread(Multythread::MatrixMul, std::ref(md3), std::ref(md1), std::ref(md2), start, end);

                start = end;
                end += step;
            }

            t1 = tick();

            for (int i = 0; i < threadsQty; i++)
            {
                threads[i].join();
            }

            t2 = tick();

            time_sum += toNanoSecs(t2 - t1).count();
        }

        std::cout << n << "," << (time_sum / repeatsQty) << '\n';

        delete[] md1.data;
        delete[] md2.data;
        delete[] md3.data;
    }

    delete[] threads;
}

