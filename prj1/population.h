#ifndef __POPUL_H__
#define __POPUL_H__

#include "global.h"
#include "chromosome.h"

#include <algorithm>

#define NUM_SELECTION 10

using namespace std;

class Population{
public:
    Population();
    Population(Graph*);
    Population(Graph*, int);

    double get_avg_quality();
    Chromosome get_best_chromosome();
    void set_pop(vector<Chromosome*>);

    static Population* evolution(Population*);

    // For Debug
    void print_pop();

private:
    int m_num_generation;
    Graph* m_graph;
    vector<Chromosome*> m_pop;

    pair<Chromosome*, Chromosome*> m_select();
    Chromosome* m_roulette_select();
    double m_calculate_fitness(int);
};

#endif
