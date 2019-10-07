#ifndef AAL01_EDITDISTANCE_METHOD_H_
#define AAL01_EDITDISTANCE_METHOD_H_

template<typename _Word_t>
class EditDistanceMethod {
public:
    EditDistanceMethod() :
        insertCost(1), deleteCost(1), replaceCost(1)
    {}
    virtual ~EditDistanceMethod() = default;

    virtual int distance(_Word_t w1, int n1, _Word_t w2, int n2) = 0;
    virtual int **raw(_Word_t w1,int n1, _Word_t w2, int n2) = 0;

    inline void
    setInsertCost(int cost) {
        insertCost = cost;
    }

    inline void
    setDeleteCost(int cost) {
        deleteCost = cost;
    }

    inline void
    setReplaceCost(int cost) {
        replaceCost = cost;
    }

protected:
    int insertCost;
    int deleteCost;
    int replaceCost;
};

#endif // AAL01_EDITDISTANCE_METHOD_H_

