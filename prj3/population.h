#ifndef __POPUL_H__
#define __POPUL_H__

#include "global.h"
#include "chromosome.h"

#include <algorithm>

#define MAX_FITNESS 3.0
#define MIN_FITNESS 1.0

using namespace std;

class Population{
public:

    /* Constructors */
    Population();
    Population(Graph*);
    Population(Graph*, int);

    ~Population();


    /* Getter & Setters */
    double get_avg_quality();
    Chromosome get_best_chromosome();
    void set_pop(vector<Chromosome*>);
    double get_avg_hamming_distance();
    double get_mutation_ratio();

    /* Interface for GA */
    static Population* evolution(Population*);

    /* Interface for LS */
    static void local_search(Population*);

    bool is_termination_condition(double, clock_t, long);

    /* print for debug */
    void print_pop();

private:
    int                     m_num_generation;
    Graph *                 m_graph;
    vector<Chromosome*>     m_pop;
    int **                  m_hamming_distance;
    double                  m_avg_hamming_distance;
    double                  m_mutation_ratio;

    /* Genetic Algorithm methods */
    pair<Chromosome*, Chromosome*> m_select();
    Chromosome* m_roulette_select();
    Chromosome* m_ranking_select();
    Chromosome* m_farthest_select(Chromosome*);
    double m_calculate_fitness(int);
    double m_calculate_fitness();

    double m_check_convergence();

    void m_calculate_ham_dist();
    void m_calculate_mutation_ratio();
};

#endif
