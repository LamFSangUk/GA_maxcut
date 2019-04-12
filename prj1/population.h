#ifndef __POPUL_H__
#define __POPUL_H__

#include "global.h"
#include "chromosome.h"

using namespace std;

class Population{
public:
    Population();
    Population(int);

    // For Debug
    void print_pop();

private:
    vector<Chromosome> m_pop;
};

#endif
