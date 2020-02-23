#ifndef AALAB03_SHAKERSORT_H_
#define AALAB03_SHAKERSORT_H_

#include "Sort.h"

#define swp(val1, val2) { auto tmp = val1; val1 = val2; val2 = tmp; }

template <typename Type>
void shakersort(Type *arr, int len, bool (*comp)(Type, Type))
{
    int low = 0;
    int high = len - 1;

    while (low <= high)
    {
        for (int idx = low; idx < high; idx++)
        {
            if (comp(arr[idx], arr[idx + 1]))
            {
                swp(arr[idx], arr[idx + 1]);
            }
        }
        high--;

        for (int idx = high; idx > low; idx--)
        {
            if (comp(arr[idx - 1], arr[idx]))
            {
                swp(arr[idx], arr[idx - 1]);
            }
        }
        low++;
    }
}

#undef swp

#endif // AALAB03_SHAKERSORT_H_

