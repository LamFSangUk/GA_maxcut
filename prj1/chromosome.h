#ifndef __CHROM_H__
#define __CHROM_H__

#include "global.h"

using namespace std;

class Chromosome{
public:
    Chromosome();
    Chromosome(Graph*, int);

    vector<int> get_gene();

    // For Debug
    void print_chrom();

private:
    Graph* m_graph;
    vector<int> m_gene;
    double m_fitness;

    // Genetic Algorithm
    friend class Population;

    Chromosome* m_crossover(Chromosome, Chromosome);
    void m_mutation(double);
    
    void m_calculate_fitness();
};

#endif
