#include <iostream>

#include "Utility.h"
#include "BruteSalesman.h"

using namespace std;

int main()
{
    size_t n;

    cin >> n;
    size_t **distances;

    Util::scanMatrix(distances, n, n);
    Util::typeMatrix(distances, n, n);
    cout << '\n';

    size_t dist;
    size_t **way;
    BruteSalesman s;

    s.set(distances, n);
    way = s(dist);

    Util::typeMatrix(way, 1, n);
    cout << dist << '\n';

    delete[] way;
    delete[] distances;

    return 0;
}

