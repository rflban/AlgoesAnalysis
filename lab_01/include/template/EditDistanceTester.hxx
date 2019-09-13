#ifndef AAL01_EDITDISTANCETESTER_HXX_
#define AAL01_EDITDISTANCETESTER_HXX_

#include "EditDistanceTester.h"

#include "WagnerFischer.h"
#include "LevenshteinRecursive.h"
#include "DamerauLevenshtein.h"
#include "DamerauLevenshteinRecursive.h"

template<typename _Word_t, class _WordHandler>
EditDistanceTester<_Word_t, _WordHandler>::EditDistanceTester() :
    method(new LevenshteinRecursive<_Word_t>)
{
}

template<typename _Word_t, class _WordHandler>
EditDistanceTester<_Word_t, _WordHandler>::~EditDistanceTester() {
    delete method;
}

template<typename _Word_t, class _WordHandler>
int EditDistanceTester<_Word_t, _WordHandler>::calculate(_Word_t w1, _Word_t w2) {
    int res;

    start();
    res = method->distance(w1, _WordHandler::len(w1), w2, _WordHandler::len(w2));
    stop();

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

#endif // AAL01_EDITDISTANCETESTER_HXX_

