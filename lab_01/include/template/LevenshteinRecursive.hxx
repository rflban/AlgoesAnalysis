#ifndef AAL01_LEVENSHTEINRECURSIVE_HXX_
#define AAL01_LEVENSHTEINRECURSIVE_HXX_

#include "LevenshteinRecursive.h"

template<typename _Word_t>
int LevenshteinRecursive<_Word_t>::distance(_Word_t w1, int n1, _Word_t w2, int n2) {
    if (n1 <= 0) {
        return n2 * insertCost;
    }
    if (n2 <= 0) {
        return n1 * deleteCost;
    }

    bool isSame = w1[n1 - 1] == w2[n2 - 1];

    int res = std::min(std::min(distance(w1, n1 - 1, w2, n2) + deleteCost,
                                distance(w1, n1, w2, n2 - 1) + insertCost),
                       distance(w1, n1 - 1, w2, n2 - 1) + replaceCost * !isSame);

    return res;
}

template<typename _Word_t>
int **LevenshteinRecursive<_Word_t>::raw(_Word_t, int, _Word_t, int) {
    return nullptr;
}

#endif // AAL01_LEVENSHTEINRECURSIVE_HXX_

