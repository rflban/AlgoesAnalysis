#ifndef AAL01_EDITDISTANCETESTER_H_
#define AAL01_EDITDISTANCETESTER_H_

#include "EditDistanceCalculator.h"
#include "TestManager.h"

class CharWordHandler;

template<typename _Word_t>
class EditDistanceMethod;

template<typename _Word_t, class _WordHandler = CharWordHandler>
class EditDistanceTester : public EditDistanceCalculator<_Word_t>, public TestManager {
public:
    EditDistanceTester();
    ~EditDistanceTester();

    int calculate(_Word_t w1, _Word_t w2) override;

    void toWagnerFischer();
    void toLevenshteinRec();
    void toDamerauLevenshtein();
    void toDamerauLevenshteinRec();

private:
    EditDistanceMethod<_Word_t> *method;
};

#include "template/EditDistanceTester.hxx"

int a;

#endif // AAL01_EDITDISTANCETESTER_H_

