#include "Salesman.h"

size_t Salesman::distance(size_t *way, size_t qty)
{
    size_t dist = 0;

    for (size_t idx = 0; idx < qty; idx++)
    {
        if (way[idx] >= len || way[(idx + 1) % qty] >= len)
        {
            return -1;
        }
        else
        {
            dist += distances[way[idx]][way[(idx + 1) % qty]];
        }
    }

    return dist;
}

