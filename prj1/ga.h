#ifndef __GA_H__
#define __GA_H__

#include "global.h"
#include "population.h"
#include "graph.h"

class GA{
public:
    GA();
    GA(Graph*, int);

    void run();

private:
    Graph* m_graph;

    Population* m_pop_cur;
    Population* m_pop_next;
};

#endif
