#ifndef __CHROM_H__
#define __CHROM_H__

#include "global.h"

#include <algorithm>

#define NORMALIZE

#define UNIFORM_CROSSOVER_THRESHOLD 0.6
#define MUTATION_THRESHOLD 0.01
#define MIN_MUTATION_RATIO 0.01
#define MAX_MUTATION_RATIO 0.05

using namespace std;

class Chromosome{
public:
    
    /* Constructors */
    Chromosome();
    Chromosome(Graph*);
    Chromosome(Graph*, int);

    Chromosome(const Chromosome &ch);

    /* Getter & Setters */
    vector<int>     get_gene();
    double          get_quality();
    void            set_fitness(double);
    double          get_fitness();
   
    /* Interface for GA */
    static Chromosome* crossover(Chromosome*,Chromosome*);
    static Chromosome* mutate(Chromosome*,double);

    static Chromosome* local_search(Chromosome*);
    static int calculate_hamming_distance(Chromosome*, Chromosome*);

    /* Operator overloading */
    bool operator<(const Chromosome&);
    bool operator==(const Chromosome&);

    static bool comp_by_quality(Chromosome*,Chromosome*);   // Comparing method

    /* print for debug */
    void print_chrom();

private:
    Graph*          m_graph;
    vector<int>     m_gene;
    double          m_quality;
    double          m_fitness;

    friend class Population;

    /* Genetic Algorithm methods */
    void m_normalize();
    void m_one_point_crossover(Chromosome*, Chromosome*);
    void m_uniform_crossover(Chromosome*, Chromosome*);
    void m_typical_mutate(double);
    int m_variation_moving_vertex(int);
    
    void m_calculate_quality();
};

#endif
