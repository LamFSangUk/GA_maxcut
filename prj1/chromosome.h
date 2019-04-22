#ifndef __CHROM_H__
#define __CHROM_H__

#include "global.h"

#define NORMALIZE

#define EQUAL_CROSSOVER_THRESHOLD 0.6
#define MUTATION_THRESHOLD 0.01

using namespace std;

class Chromosome{
public:
    
    /* Constructors */
    Chromosome();
    Chromosome(Graph*);
    Chromosome(Graph*, int);

    /* Getter & Setters */
    vector<int>     get_gene();
    double          get_quality();
    void            set_fitness(double);
    double          get_fitness();
   
    /* Interface for GA */
    static Chromosome* crossover(Chromosome*,Chromosome*);

    /* Operator overloading */
    bool operator<(const Chromosome&);

    static bool comp_by_quality(Chromosome*,Chromosome*);   // Comparing method

    /* print for debug */
    void print_chrom();

private:
    Graph*          m_graph;
    vector<int>     m_gene;
    double          m_quality;
    double          m_fitness;

    friend class Population;

    /* Genetic Algoritm methods */
    void m_normalize();
    void m_one_point_crossover(Chromosome*, Chromosome*);
    void m_equal_crossover(Chromosome*, Chromosome*);
    void m_mutate(double);
    void m_typical_mutate(double);
    
    void m_calculate_quality();
};

#endif
