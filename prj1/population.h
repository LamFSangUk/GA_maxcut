#ifndef __POPUL_H__
#define __POPUL_H__

#include "global.h"
#include "chromosome.h"

using namespace std;

class Population{
public:
    Population();
    Population(Graph*, int);

    double get_avg_fitness();
    // For Debug
    void print_pop();

private:
    Graph* m_graph;
    vector<Chromosome> m_pop;
};

#endif
