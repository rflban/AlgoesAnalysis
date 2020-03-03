#ifndef AA06_ANTCOLONY_H_
#define AA06_ANTCOLONY_H_

#include "Salesman.h"

class AntColony : public Salesman
{
public:
    AntColony(double alpha=0.4, double beta=0.6,
              double rho=0.5, int t_max=1000);

    size_t **operator()(size_t &dist) override;

private:
    double alpha;
    double beta;
    double rho;
    double t_max;
};

#endif // AA06_ANTCOLONY_H_

