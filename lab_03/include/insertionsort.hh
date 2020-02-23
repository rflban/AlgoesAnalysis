#ifndef AALAB03_INSERTIONSORT_H_
#define AALAB03_INSERTIONSORT_H_

#include "Sort.h"

#define swp(val1, val2) { auto tmp = val1; val1 = val2; val2 = tmp; }

template <typename Type>
void insertionsort(Type *arr, int len, bool (*comp)(Type, Type))
{
    for (int i = 1; i < len; i++)
    {
        for (int j = i; j > 0 && comp(arr[j - 1], arr[j]); j--)
        {
            swp(arr[j], arr[j - 1]);
        }
    }
}

#undef swp

#endif // AALAB03_INSERTIONSORT_H_

