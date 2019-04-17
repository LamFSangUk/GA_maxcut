#ifndef __CHROM_H__
#define __CHROM_H__

#include "global.h"

using namespace std;

class Chromosome{
public:
    Chromosome();
    Chromosome(Graph*);
    Chromosome(Graph*, int);

    vector<int> get_gene();
    double get_quality();
    void set_fitness(double);
    double get_fitness();
   
    static Chromosome* crossover(Chromosome*,Chromosome*);

    // Operator overloading
    bool operator<(const Chromosome&);

    static bool comp_by_quality(Chromosome*,Chromosome*);

    // For Debug
    void print_chrom();

private:
    Graph* m_graph;
    vector<int> m_gene;
    double m_quality;
    double m_fitness;

    // Genetic Algorithm
    friend class Population;

    void m_one_point_crossover(Chromosome*, Chromosome*);
    void m_mutate(double);
    void m_typical_mutate(double);
    
    void m_calculate_quality();
};

#endif
