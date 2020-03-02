#include "BruteSalesman.h"

#include "Utility.h"

#define swp(a, b) { auto tmp = a; a = b; b = tmp; }

struct BruteSalesman::WayDescriptor
{
    size_t **way;
    size_t dist;
};

void BruteSalesman::bruteforce(WayDescriptor &wd, size_t **currentWay, size_t currentCity)
{
    if (currentCity >= length())
    {
        size_t dist = distance(*currentWay, length());

        if (wd.dist > dist)
        {
            delete[] wd.way;
            wd = { Util::copyMatrix(currentWay, 1, length()), dist };
        }
    }
    else
    {
        bruteforce(wd, currentWay, currentCity + 1);

        for (size_t i = currentCity + 1; i < length(); i++)
        {
            swp(currentWay[0][currentCity], currentWay[0][i]);
            bruteforce(wd, currentWay, currentCity + 1);
            swp(currentWay[0][currentCity], currentWay[0][i]);
        }
    }
}

size_t **BruteSalesman::operator()(size_t &minDist)
{
    size_t **initWay;
    WayDescriptor minwd = { Util::createMatrix<size_t>(1, length()), (size_t)-1 };

    for (size_t idx = 0; idx < length(); idx++)
    {
        minwd.way[0][idx] = idx;
    }
    initWay = Util::copyMatrix(minwd.way, 1, length());

    bruteforce(minwd, initWay, 1);

    delete[] initWay;

    minDist = minwd.dist;
    return minwd.way;
}

