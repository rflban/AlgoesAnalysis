#include <iostream>
#include <chrono>
#include <random>
#include <ctime>

#include <thread>
#include <mutex>
#include <queue>

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

void timeTest(bool useConveyor);

class MatrixMulReader
{
public:
    virtual struct MatrixMul operator()() = 0;
    virtual operator bool() = 0;
};

class MatrixMulRepeater : public MatrixMulReader
{
public:
    MatrixMulRepeater(int qty, double **m1, double **m2,
                      size_t n, size_t m, size_t r) :
        qty(qty), m1(m1), m2(m2),
        n(n), m(m), r(r)
    {
    }

    struct MatrixMul operator()() override
    {
        struct MatrixMul mm(m1, m2, n, m, r);
        if (qty <= 0)
        {
            mm = { 0, 0, 0, 0, 0 };
        }

        qty--;

        return mm;
    }

    operator bool() override
    {
        return qty > 0;
    }

private:
    int qty;

    double **m1;
    double **m2;
    size_t n;
    size_t m;
    size_t r;
};

class Multythread
{
public:
    static
    void MatrixMul(MatrixDescriptor &res, MatrixDescriptor &md1, MatrixDescriptor &md2,
                   size_t start, size_t end)
    {
        ::MatrixMul(res.data + start, md1.data  + start, md2.data, end - start, md2.m, md1.m);
    }
};


class Conveyor
{
public:
    static
    void do1(MatrixMulReader *mmr)
    {
        while (*mmr)
        {
            auto mm = (*mmr)();
            mm.allocateMemory();

            m12.lock();
            q12.push(mm);
            m12.unlock();
        }

        isP1Ended = true;
    }
    static
    void do2()
    {
        while (!q12.empty() || !isP1Ended)
        {
            if (!q12.empty())
            {
                //m12.lock();
                //q12.front().calculateMulh();
                //q23.push(q12.front());
                //q12.pop();
                //m12.lock();

                m12.lock();
                struct MatrixMul mm = q12.front();;
                q12.pop();
                m12.unlock();

                mm.calculateMulh();

                m23.lock();
                q23.push(mm);
                m23.unlock();
            }
        }

        isP1Ended = false;
        isP2Ended = true;
    }
    static
    void do3()
    {
        while (!q23.empty() || !isP2Ended)
        {
            if (!q23.empty())
            {
                //m12.lock();
                //q23.front().calculateMulv();
                //q34.push(q23.front());
                //q23.pop();
                //m12.unlock();

                m23.lock();
                struct MatrixMul mm = q23.front();
                q23.pop();
                m23.unlock();

                mm.calculateMulv();

                m34.lock();
                q34.push(mm);
                m34.unlock();
            }
        }

        isP2Ended = false;
        isP3Ended = true;
    }
    static
    void do4()
    {
        while (!q34.empty() || !isP3Ended)
        {
            if (!q34.empty())
            {
                //m12.lock();
                //q34.front().calculatePart1();
                //q45.push(q34.front());
                //q34.pop();
                //m12.unlock();

                m34.lock();
                struct MatrixMul mm = q34.front();
                q34.pop();
                m34.unlock();

                mm.calculatePart1();

                m45.lock();
                q45.push(mm);
                m45.unlock();
            }
        }

        isP3Ended = false;
        isP4Ended = true;
    }
    static
    void do5()
    {
        while (!q45.empty() || !isP4Ended)
        {
            if (!q45.empty())
            {
                //m12.lock();
                //q45.front().calculatePart2();
                //q56.push(q45.front());
                //q45.pop();
                //m12.unlock();

                m45.lock();
                struct MatrixMul mm = q45.front();
                q45.pop();
                m45.unlock();

                mm.calculatePart2();

                m56.lock();
                q56.push(mm);
                m56.unlock();
            }
        }

        isP4Ended = false;
        isP5Ended = true;
    }
    static
    void do6()
    {
        while (!q56.empty() || !isP5Ended)
        {
            if (!q56.empty())
            {
                //m12.lock();
                //q56.front().calculateUneven();
                //q67.push(q56.front());
                //q56.pop();
                //m12.unlock();

                m56.lock();
                struct MatrixMul mm = q56.front();
                q56.pop();
                m56.unlock();

                mm.calculateUneven();

                q67.push(mm);
            }
        }

        isP5Ended = false;
    }

    static std::queue<struct MatrixMul> q12;
    static std::queue<struct MatrixMul> q23;
    static std::queue<struct MatrixMul> q34;
    static std::queue<struct MatrixMul> q45;
    static std::queue<struct MatrixMul> q56;
    static std::queue<struct MatrixMul> q67;

    static std::mutex m12;
    static std::mutex m23;
    static std::mutex m34;
    static std::mutex m45;
    static std::mutex m56;
    static std::mutex m67;

    static bool isP1Ended;
    static bool isP2Ended;
    static bool isP3Ended;
    static bool isP4Ended;
    static bool isP5Ended;
    static bool isP6Ended;
    static bool isP7Ended;
};
std::queue<struct MatrixMul> Conveyor::q12 = {};
std::queue<struct MatrixMul> Conveyor::q23 = {};
std::queue<struct MatrixMul> Conveyor::q34 = {};
std::queue<struct MatrixMul> Conveyor::q45 = {};
std::queue<struct MatrixMul> Conveyor::q56 = {};
std::queue<struct MatrixMul> Conveyor::q67 = {};

std::mutex Conveyor::m12;
std::mutex Conveyor::m23;
std::mutex Conveyor::m34;
std::mutex Conveyor::m45;
std::mutex Conveyor::m56;
std::mutex Conveyor::m67;

bool Conveyor::isP1Ended = false;
bool Conveyor::isP2Ended = false;
bool Conveyor::isP3Ended = false;
bool Conveyor::isP4Ended = false;
bool Conveyor::isP5Ended = false;
bool Conveyor::isP6Ended = false;
bool Conveyor::isP7Ended = false;

int main(int argc, char **argv)
{
    bool doTest = false;
    bool useConveyor = true;

    for (int i = 1; i < argc; i++)
    {
        if (argv[i][0] == 't')
        {
            doTest = true;
        }
        else if (argv[i][0] == 'l')
        {
            useConveyor = false;
            doTest = true;
        }
    }

    int n;

    if (doTest)
    {
        timeTest(useConveyor);
        exit(0);
    }

    std::cin >> n;

    if (!std::cin.good() || n <= 0)
    {
        exit(1);
    }

    double **matrix1 = readMatrix(n, n);
    double **matrix2 = readMatrix(n, n);

    if (matrix1 == nullptr || matrix2 == nullptr)
    {
        exit(1);
    }

    int rpt = 100;
    MatrixMulRepeater mmr(rpt, matrix1, matrix2, n, n, n);
    auto thread1 = std::thread(Conveyor::do1, &mmr);
    auto thread2 = std::thread(Conveyor::do2);
    auto thread3 = std::thread(Conveyor::do3);
    auto thread4 = std::thread(Conveyor::do4);
    auto thread5 = std::thread(Conveyor::do5);
    auto thread6 = std::thread(Conveyor::do6);

    thread1.join();
    thread2.join();
    thread3.join();
    thread4.join();
    thread5.join();
    thread6.join();

    printf("Matrix len: %d\n", n);
    printMatrix(matrix1, n, n);
    printf("\n");
    printMatrix(matrix2, n, n);
    printf("\n");
    printMatrix(Conveyor::q67.front().res, n, n);

    for (int i = 0; i < rpt; i++)
    {
        delete[] Conveyor::q67.front().res;
        Conveyor::q67.pop();
    }

    delete[] matrix1;
    delete[] matrix2;

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

void timeTest(bool useConveyor)
{
    TimePoint t1, t2;
    std::chrono::steady_clock::rep time_sum = 0;

    int n = 100;
    int h = 100;
    int maxN = 1000;
    int repeatsQty = 5;

    int msize = 101;
    double **res = Util::createMatrix<double>(msize, msize);
    double **matrix1 = Util::createMatrix<double>(msize, msize);
    double **matrix2 = Util::createMatrix<double>(msize, msize);
    randomFill(matrix1, msize, msize);
    randomFill(matrix2, msize, msize);

    std::cout << "qty,time" << '\n';

    for (; n <= maxN; n += h)
    {
        time_sum = 0;

        for (int j = 0; j < repeatsQty; j++)
        {
            if (useConveyor)
            {
                MatrixMulRepeater mmr(n, matrix1, matrix2, msize, msize, msize);

                auto thread1 = std::thread(Conveyor::do1, &mmr);
                auto thread2 = std::thread(Conveyor::do2);
                auto thread3 = std::thread(Conveyor::do3);
                auto thread4 = std::thread(Conveyor::do4);
                auto thread5 = std::thread(Conveyor::do5);
                auto thread6 = std::thread(Conveyor::do6);

                t1 = tick();

                thread1.join();
                thread2.join();
                thread3.join();
                thread4.join();
                thread5.join();
                thread6.join();

                t2 = tick();

                //for (int i = 0; i < n; i++)
                //{
                    //delete[] Conveyor::q67.front().res;
                    //Conveyor::q67.pop();
                //}
                while (!Conveyor::q67.empty())
                {
                    delete[] Conveyor::q67.front().res;
                    Conveyor::q67.pop();
                }
            }
            else
            {
                t1 = tick();

                for (int i = 0; i < n; i++)
                {
                    struct MatrixMul mm(matrix1, matrix2, msize, msize, msize);
                    mm.allocateMemory();
                    mm.calculateMulh();
                    mm.calculateMulv();
                    mm.calculatePart1();
                    mm.calculatePart2();
                    mm.calculateUneven();
                    delete[] mm.res;
                    //MatrixMul(res, matrix1, matrix2, msize, msize, msize);
                }

                t2 = tick();
            }

            time_sum += toNanoSecs(t2 - t1).count();
        }

        std::cout << n << "," << (time_sum / repeatsQty) << '\n';
    }

    delete[] res;
    delete[] matrix1;
    delete[] matrix2;
}

