#ifndef AAL01_DAMERAULEVENSHTEINRECURSIVE_H_
#define AAL01_DAMERAULEVENSHTEINRECURSIVE_H_

#include "EditDistanceMethod.h"

template<typename _Word_t>
class DamerauLevenshteinRecursive : public EditDistanceMethod<_Word_t> {
public:
    DamerauLevenshteinRecursive();
    virtual ~DamerauLevenshteinRecursive() = default;

    int distance(_Word_t w1, int n1, _Word_t w2, int n2) override;

    inline void
    setTransposeCost(int cost) {
        transposeCost = cost;
    }

protected:
    using EditDistanceMethod<_Word_t>::insertCost;
    using EditDistanceMethod<_Word_t>::deleteCost;
    using EditDistanceMethod<_Word_t>::replaceCost;

    int transposeCost;
};

#include "template/DamerauLevenshteinRecursive.hxx"

#endif // AAL01_DAMERAULEVENSHTEINRECURSIVE_H_

