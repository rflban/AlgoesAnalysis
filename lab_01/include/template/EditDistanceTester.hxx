#ifndef AAL01_EDITDISTANCETESTER_HXX_
#define AAL01_EDITDISTANCETESTER_HXX_

#include "EditDistanceTester.h"

#include "WagnerFischer.h"
#include "LevenshteinRecursive.h"
#include "DamerauLevenshtein.h"
#include "DamerauLevenshteinRecursive.h"

#include <iostream>

template<typename _Word_t, class _WordHandler>
EditDistanceTester<_Word_t, _WordHandler>::EditDistanceTester() :
    method(new LevenshteinRecursive<_Word_t>),
    showOptInfo(false)
{
}

template<typename _Word_t, class _WordHandler>
EditDistanceTester<_Word_t, _WordHandler>::~EditDistanceTester() {
    delete method;
}

template<typename _Word_t, class _WordHandler>
int EditDistanceTester<_Word_t, _WordHandler>::calculate(_Word_t w1, _Word_t w2) {
    int res;
    int n1 = _WordHandler::len(w1);
    int n2 = _WordHandler::len(w2);

    start();
    res = method->distance(w1, n1, w2, n2);
    stop();

    if (showOptInfo) {
        int **matrix = method->raw(w1, n1, w2, n2);

        if (matrix) {
            for (int i = 0; i <= n1; i++) {
                for (int j = 0; j <= n2; j++) {
                    std::cout << matrix[i][j] << " ";
                }

                std::cout << '\n';
            }
            std::cout << '\n';

            delete[] matrix;
        }
    }

    return res;
}

template<typename _Word_t, class _WordHandler>
void EditDistanceTester<_Word_t, _WordHandler>::toWagnerFischer() {
    delete method;
    method = new WagnerFischer<_Word_t>;
}

template<typename _Word_t, class _WordHandler>
void EditDistanceTester<_Word_t, _WordHandler>::toLevenshteinRec() {
    delete method;
    method = new LevenshteinRecursive<_Word_t>;
}

template<typename _Word_t, class _WordHandler>
void EditDistanceTester<_Word_t, _WordHandler>::toDamerauLevenshtein() {
    delete method;
    method = new DamerauLevenshtein<_Word_t>;
}

template<typename _Word_t, class _WordHandler>
void EditDistanceTester<_Word_t, _WordHandler>::toDamerauLevenshteinRec() {
    delete method;
    method = new DamerauLevenshteinRecursive<_Word_t>;
}

template<typename _Word_t, class _WordHandler>
void EditDistanceTester<_Word_t, _WordHandler>::enableOptInfo() {
    showOptInfo = true;
}

template<typename _Word_t, class _WordHandler>
void EditDistanceTester<_Word_t, _WordHandler>::disableOptInfo() {
    showOptInfo = false;
}

#endif // AAL01_EDITDISTANCETESTER_HXX_

