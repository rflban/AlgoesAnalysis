#ifndef AAL01_DAMERAULEVENSHTEINRECURSIVE_HXX_
#define AAL01_DAMERAULEVENSHTEINRECURSIVE_HXX_

#include "DamerauLevenshteinRecursive.h"

template<typename _Word_t>
DamerauLevenshteinRecursive<_Word_t>::DamerauLevenshteinRecursive() :
    transposeCost(1)
{}

template<typename _Word_t>
int DamerauLevenshteinRecursive<_Word_t>::distance(_Word_t w1, int n1, _Word_t w2, int n2) {
    if (n1 == 0) {
        return n2 * insertCost;
    }
    if (n2 == 0) {
        return n1 * deleteCost;
    }

    bool isSame = w1[n1 - 1] == w2[n2 - 1];

    int res = std::min(std::min(distance(w1, n1 - 1, w2, n2) + deleteCost,
                                distance(w1, n1, w2, n2 - 1) + insertCost),
                       distance(w1, n1 - 1, w2, n2 - 1) + replaceCost * !isSame);

    if (n1 > 1 && n2 > 1) {
        if (w1[n1 - 1] == w2[n2 - 2] && w1[n1 - 2] == w2[n2 - 1]) {
            res = std::min(distance(w1, n1 - 2, w2, n2 - 2) + transposeCost, res);
        }
    }

    return res;
}

#endif // AAL01_DAMERAULEVENSHTEINRECURSIVE_HXX_

