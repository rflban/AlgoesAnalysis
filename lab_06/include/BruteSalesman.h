#ifndef AA06_BRUTESALESMAN_H_
#define AA06_BRUTESALESMAN_H_

#include "Salesman.h"

class BruteSalesman : public Salesman
{
public:
    size_t **operator()(size_t &minDist) override;

private:
    struct WayDescriptor;

    void bruteforce(WayDescriptor &wd, size_t **currentWay, size_t currentCity);
};

#endif // AA06_BRUTESALESMAN_H_

