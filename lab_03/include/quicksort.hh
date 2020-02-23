#ifndef AALAB03_QUICKSORT_H_
#define AALAB03_QUICKSORT_H_

#include "Sort.h"

#define swp(val1, val2) { auto tmp = val1; val1 = val2; val2 = tmp; }

template <typename Type>
static int parition(Type *arr, int low, int high, bool (*comp)(Type, Type))
{
    int i = low;
    Type pivot = arr[high];

    for (int j = low; j < high; j++)
    {
        if (comp(pivot, arr[j]))
        {
            swp(arr[i], arr[j]);
            i++;
        }
    }

    swp(arr[i], arr[high]);

    return i;
}

template <typename Type>
static void qsrec(Type *arr, int low, int high, bool (*comp)(Type, Type))
{
    if (low < high)
    {
        int p = parition(arr, low, high, comp);

        qsrec(arr, low, p - 1, comp);
        qsrec(arr, p + 1, high, comp);
    }
}

template <typename Type>
void quicksort(Type *arr, int len, bool (*comp)(Type, Type))
{
    qsrec(arr, 0, len - 1, comp);
}

#undef swp

#endif // AALAB03_QUICKSORT_H_

