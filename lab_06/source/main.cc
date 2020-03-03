#include <iostream>

#include "Utility.h"
#include "BruteSalesman.h"
#include "AntColony.h"

using namespace std;

int main(int argc, char **argv)
{
    Salesman *salesman = new AntColony;

    for (int i = 1; i < argc; i++)
    {
        if (argv[i][0] == '1')
        {
            delete salesman;
            salesman = new BruteSalesman;
        }
        if (argv[i][0] == '2')
        {
            // skip
        }
    }

    size_t n;

    cin >> n;
    size_t **distances;

    Util::scanMatrix(distances, n, n);
    Util::typeMatrix(distances, n, n);
    cout << '\n';

    size_t dist;
    size_t **way;

    salesman->set(distances, n);
    way = (*salesman)(dist);

    Util::typeMatrix(way, 1, n);
    cout << dist << '\n';

    delete salesman;

    delete[] way;
    delete[] distances;

    return 0;
}

