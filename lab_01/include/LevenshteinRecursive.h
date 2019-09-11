#ifndef AAL01_LEVENSHTEINRECURSIVE_H_
#define AAL01_LEVENSHTEINRECURSIVE_H_

#include "EditDistanceMethod.h"

template <typename _Word_t>
class LevenshteinRecursive : public EditDistanceMethod<_Word_t> {
public:
    LevenshteinRecursive() = default;
    virtual ~LevenshteinRecursive() = default;

    int distance(_Word_t w1, int n1, _Word_t w2, int n2) override;

protected:
    using EditDistanceMethod<_Word_t>::insertCost;
    using EditDistanceMethod<_Word_t>::deleteCost;
    using EditDistanceMethod<_Word_t>::replaceCost;
};

#include "template/LevenshteinRecursive.hxx"

#endif // AAL01_LEVENSHTEINRECURSIVE_H_

