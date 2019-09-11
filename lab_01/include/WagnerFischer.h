#ifndef AAL01_WAGNERFISCHER_H_
#define AAL01_WAGNERFISCHER_H_

#include "EditDistanceMethod.h"

template <typename _Word_t>
class WagnerFischer : public EditDistanceMethod<_Word_t> {
public:
    WagnerFischer() = default;
    virtual ~WagnerFischer() = default;

    int distance(_Word_t w1, int n1, _Word_t w2, int n2) override;

protected:
    using EditDistanceMethod<_Word_t>::insertCost;
    using EditDistanceMethod<_Word_t>::deleteCost;
    using EditDistanceMethod<_Word_t>::replaceCost;
};

#include "template/WagnerFischer.hxx"

#endif // AAL01_WAGNERFISCHER_H_

