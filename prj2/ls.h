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
#endif
