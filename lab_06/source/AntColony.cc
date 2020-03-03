#include "AntColony.h"

#include <cmath>
#include <ctime>

#include <random>

#include "Utility.h"

AntColony::AntColony(double alpha, double beta, double rho, int t_max) :
    alpha(alpha), beta(beta), rho(rho), t_max(t_max)
{
}

size_t **AntColony::operator()(size_t &dist)
{
    std::mt19937 rnd(time(0));

    double **pheromone = Util::createMatrix<double>(length(), length());
    for (size_t i = 0; i < length(); i++)
    {
        for (size_t j = 0; j < length(); j++)
        {
            pheromone[i][j] = 0.1;
        }
    }

    size_t minDist = -1;
    size_t **minWay = Util::createMatrix<size_t>(1, length());

    size_t **p = Util::createMatrix<size_t>(1, length());
    size_t **way = Util::createMatrix<size_t>(1, length());
    size_t **cities = Util::createMatrix<size_t>(1, length());

    double **delta = Util::createMatrix<double>(length(), length());

    for (int time = 0; time < t_max; time++)
    {
        for (size_t antCity = 0; antCity < length(); antCity++)
        {
            for (size_t i = 0; i < length(); i++)
            {
                cities[0][i] = 0;
                way[0][i] = 0;
            }

            cities[0][antCity] = 1;
            way[0][0] = antCity;

            size_t visitedQty = 1;
            size_t curDist = 0;

            while (visitedQty < length())
            {
                for (size_t i = 0; i < length(); i++)
                {
                    if (cities[0][i])
                    {
                        p[0][i] = 0;
                    }
                    else
                    {
                        p[0][i] =
                            pow(pheromone[way[0][visitedQty - 1]][i], alpha) *
                            pow(map()[way[0][visitedQty - 1]][i], beta);

                        double denominator = 0;

                        for (size_t q = 0; q < visitedQty; q++)
                        {
                            denominator +=
                                pow(pheromone[way[0][q]][i], alpha) *
                                pow(map()[way[0][q]][i], beta);
                        }

                        p[0][i] /= denominator;
                    }
                }

                size_t **onlyUnvisited =
                    Util::createMatrix<size_t>(1, length() - visitedQty);

                for (size_t i = 0, j = 0; i < length(); i++)
                {
                    if (!cities[0][i])
                    {
                        onlyUnvisited[0][j] = i;
                        j++;
                    }
                }

                size_t idx = rnd() % (length() - visitedQty);
                curDist += map()[way[0][visitedQty - 1]]
                                [onlyUnvisited[0][idx]];

                visitedQty++;
                way[0][visitedQty - 1] = onlyUnvisited[0][idx];
                cities[0][onlyUnvisited[0][idx]] = 1;

                delete[] onlyUnvisited;
            }

            curDist += map()[way[0][0]][way[0][length() - 1]];

            for (size_t i = 0; i < length() - 1; i++)
            {
                delta[way[0][i]][way[0][i + 1]] += (double)minDist / curDist;
                delta[way[0][i + 1]][way[0][i]] += (double)minDist / curDist;
            }

            if (curDist < minDist)
            {
                delete[] minWay;

                minDist = curDist;
                minWay = Util::copyMatrix(way, 1, length());
            }
        }

        for (size_t i = 0; i < length(); i++)
        {
            for (size_t j = i + 1; j < length(); j++)
            {
                pheromone[i][j] *= (1 - rho);
                pheromone[i][j] += delta[i][j];
            }
        }
    }

    delete[] pheromone;
    delete[] cities;
    delete[] delta;
    delete[] way;
    delete[] p;

    dist = minDist;
    return minWay;
}

