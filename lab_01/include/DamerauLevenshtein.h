#ifndef AAL01_DAMERAULEVENSHTEIN_H_
#define AAL01_DAMERAULEVENSHTEIN_H_

#include "EditDistanceMethod.h"

template<typename _Word_t>
class DamerauLevenshtein : public EditDistanceMethod<_Word_t> {
public:
    DamerauLevenshtein();
    virtual ~DamerauLevenshtein() = default;

    int distance(_Word_t w1, int n1, _Word_t w2, int n2) override;

    inline void
    setTransponseCost(int cost) {
        transposeCost = cost;
    }

protected:
    using EditDistanceMethod<_Word_t>::insertCost;
    using EditDistanceMethod<_Word_t>::deleteCost;
    using EditDistanceMethod<_Word_t>::replaceCost;

    int transposeCost;
};

#include "template/DamerauLevenshtein.hxx"

#endif // AAL01_DAMERAULEVENSHTEIN_H_

