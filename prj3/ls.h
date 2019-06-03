#ifndef __LS_H__
#define __LS_H__

#include "global.h"
#include "population.h"

class LS{
public:
    LS(Graph*,int);

    Chromosome run();

private:
    Graph* m_graph;

    Population* m_pop;
};

Chromosome* one_bit_flip_local_search(Chromosome* );

#endif
