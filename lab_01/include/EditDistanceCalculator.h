#ifndef AAL01_EDITDISTANCECALCULATOR_H_
#define AAL01_EDITDISTANCECALCULATOR_H_

template<typename _Word_t>
class EditDistanceCalculator {
public:
    virtual int calculate(_Word_t w1, _Word_t w2) = 0;
};

#endif // AAL01_EDITDISTANCECALCULATOR_H_

