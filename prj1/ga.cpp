#include "ga.h"

GA::GA()
{}

GA::GA(Graph* g, int chrom_size){
    m_graph = g;

    m_pop_cur = new Population(m_graph, chrom_size);

    // Debug
    m_pop_cur->print_pop();
}

void GA::run(){
    double avg_fitness = m_pop_cur->get_avg_fitness();
    fprintf(stdout, "1st Generation : %lf\n", avg_fitness);
}
