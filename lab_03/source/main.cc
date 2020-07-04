// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include <iostream>
#include <random>
#include <chrono>

#include "Sort.h"

using Moment = std::chrono::steady_clock::time_point;
using Duration = std::chrono::steady_clock::duration;
using TimeInt = Duration::rep;

#define tick() std::chrono::steady_clock::now()

static inline
TimeInt to_nanosecs(const Duration &d)
{
    return std::chrono::duration_cast<std::chrono::nanoseconds>(d).count();
}

bool comparator(int v1, int v2) {
    return v1 > v2;
}

int minQty = 100;
int maxQty = 10000;
int step = 100;
int REPEATS = 10;

void test(void (*sort)(int *, int, bool (*)(int, int)),
          void (*fill)(int *, int));

void fillinc(int *arr, int len);
void filldec(int *arr, int len);
void fillrnd(int *arr, int len);

int main(int argc, char **argv)
{
    void (*sort)(int *arr, int len, bool (*comp)(int, int)) = &quicksort<int>;

    bool doTest = false;
    void (*fill)(int *arr, int len) = &fillinc;

    for (int i = 1; i < argc; i++)
    {
        if (argv[i][0] == '1')
        {
            sort = &quicksort<int>;
        }
        else if (argv[i][0] == '2')
        {
            sort = &insertionsort<int>;
        }
        else if (argv[i][0] == '3')
        {
            sort = &shakersort<int>;
        }
        else if (argv[i][0] == 'i')
        {
            doTest = true;
            fill = &fillinc;
        }
        else if (argv[i][0] == 'd')
        {
            doTest = true;
            fill = &filldec;
        }
        else if (argv[i][0] == 'r')
        {
            doTest = true;
            fill = &fillrnd;
        }
    }

    if (doTest)
    {
        test(sort, fill);
        exit(0);
    }

    int len;

    std::cin >> len;

    if (len <= 0)
    {
        exit(1);
    }

    int arr[len];
    for (int i = 0; i < len; i++)
    {
        std::cin >> arr[i];

        if (!std::cin.good())
        {
            exit(1);
        }
    }
    std::cout << '\n';

    sort(arr, len, comparator);

    for (int i = 0; i < len; i++)
    {
        std::cout << arr[i] << " ";
    }
    std::cout << '\n';

    return 0;
}

void test(void (*sort)(int *, int, bool (*)(int, int)),
          void (*fill)(int *, int))
{
    TimeInt timesum;
    Moment t1, t2;
    int data[maxQty];

    std::cout << "len,time" << '\n';

    for (int len = minQty; len <= maxQty; len += step)
    {
        timesum = 0;

        for (int i = 0; i < REPEATS; i++)
        {
            fill(data, len);

            t1 = tick();
            sort(data, len, comparator);
            t2 = tick();

            timesum += to_nanosecs(t2 - t1);
        }

        std::cout << len << "," << (timesum / REPEATS) << '\n';
    }
}

void fillinc(int *arr, int len)
{
    for (int i = 0; i < len; i++)
    {
        arr[i] = i;
    }
}

void filldec(int *arr, int len)
{
    for (int i = 0; i < len; i++)
    {
        arr[i] = len - i;
    }
}

void fillrnd(int *arr, int len)
{
    std::mt19937 generator(time(NULL));

    for (int i = 0; i < len; i++)
    {
        arr[i] = generator();
    }
}

