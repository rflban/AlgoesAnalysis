#ifndef AAL01_WAGNERFISCHER_HXX_
#define AAL01_WAGNERFISCHER_HXX_

#include "WagnerFischer.h"

#include "Utility.h"

template<typename _Word_t>
int WagnerFischer<_Word_t>::distance(_Word_t w1, int n1, _Word_t w2, int n2) {
    int **D = Util::createMatrix<int>(n1 + 1, n2 + 1);
    D[0][0] = 0;

    for (int j = 1; j <= n2; j++) {
        D[0][j] = D[0][j - 1] + insertCost;
    }

    for (int i = 1; i <= n1; i++) {
        D[i][0] = D[i - 1][0] + deleteCost;

        for (int j = 1; j <= n2; j++) {
            if (w1[i - 1] == w2[j - 1]) {
                D[i][j] = D[i - 1][j - 1];
            }
            else {
                D[i][j] = std::min(std::min(D[i - 1][j] + deleteCost,
                                            D[i][j - 1] + insertCost),
                                   D[i - 1][j - 1] + replaceCost);
            }
        }
    }

    int res = D[n1][n2];
    delete[] D;

    return res;
}

template<typename _Word_t>
int **WagnerFischer<_Word_t>::raw(_Word_t w1, int n1, _Word_t w2, int n2) {
    int **D = Util::createMatrix<int>(n1 + 1, n2 + 1);
    D[0][0] = 0;

    for (int j = 1; j <= n2; j++) {
        D[0][j] = D[0][j - 1] + insertCost;
    }

    for (int i = 1; i <= n1; i++) {
        D[i][0] = D[i - 1][0] + deleteCost;

        for (int j = 1; j <= n2; j++) {
            if (w1[i - 1] == w2[j - 1]) {
                D[i][j] = D[i - 1][j - 1];
            }
            else {
                D[i][j] = std::min(std::min(D[i - 1][j] + deleteCost,
                                            D[i][j - 1] + insertCost),
                                   D[i - 1][j - 1] + replaceCost);
            }
        }
    }

    return D;
}

#endif // AAL01_WAGNERFISCHER_HXX_

