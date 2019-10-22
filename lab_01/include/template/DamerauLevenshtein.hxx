#ifndef AAL01_DAMERAULEVENSHTEIN_HXX_
#define AAL01_DAMERAULEVENSHTEIN_HXX_

#include "DamerauLevenshtein.h"

#include "Utility.h"

template<typename _Word_t>
DamerauLevenshtein<_Word_t>::DamerauLevenshtein() :
    transposeCost(1)
{}

template<typename _Word_t>
int DamerauLevenshtein<_Word_t>::distance(_Word_t w1, int n1, _Word_t w2, int n2) {
    int **D = Util::createMatrix<int>(n1 + 1, n2 + 1);
    D[0][0] = 0;

    for (int j = 1; j <= n2; j++) {
        D[0][j] = D[0][j - 1] + insertCost;
    }

    for (int i = 1; i <= n1; i++) {
        D[i][0] = D[i - 1][0] + deleteCost;

        for (int j = 1; j <= n2; j++) {
            int replaceCost = this->replaceCost;

            if (w1[i - 1] == w2[j - 1]) {
                replaceCost = 0;
            }

            D[i][j] = std::min(std::min(D[i - 1][j] + deleteCost,
                                        D[i][j - 1] + insertCost),
                               D[i - 1][j - 1] + replaceCost);

            if (i > 1 && j > 1) {
                if (w1[i - 1] == w2[j - 2] && w1[i - 2] == w2[j - 1]) {
                    D[i][j] = std::min(D[i - 2][j - 2] + transposeCost, D[i][j]);
                }
            }
        }
    }

    int res = D[n1][n2];
    delete[] D;

    return res;
}

template<typename _Word_t>
int **DamerauLevenshtein<_Word_t>::raw(_Word_t w1, int n1, _Word_t w2, int n2) {
    int **D = Util::createMatrix<int>(n1 + 1, n2 + 1);
    D[0][0] = 0;

    for (int j = 1; j <= n2; j++) {
        D[0][j] = D[0][j - 1] + insertCost;
    }

    for (int i = 1; i <= n1; i++) {
        D[i][0] = D[i - 1][0] + deleteCost;

        for (int j = 1; j <= n2; j++) {
            int replaceCost = this->replaceCost;

            if (w1[i - 1] == w2[j - 1]) {
                replaceCost = 0;
            }

            D[i][j] = std::min(std::min(D[i - 1][j] + deleteCost,
                                        D[i][j - 1] + insertCost),
                               D[i - 1][j - 1] + replaceCost);

            if (i > 1 && j > 1) {
                if (w1[i - 1] == w2[j - 2] && w1[i - 2] == w2[j - 1]) {
                    D[i][j] = std::min(D[i - 2][j - 2] + transposeCost, D[i][j]);
                }
            }
        }
    }

    return D;
}

#endif // AAL01_DAMERAULEVENSHTEIN_HXX_

