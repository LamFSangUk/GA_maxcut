#include "ls.h"

LS::LS(Graph* g, int chrom_size){
    m_graph = g;
    m_pop = new Population(m_graph, chrom_size);
}

Chromosome LS::run(){
    srand(time(NULL));

    Chromosome best_chrom_ever;

    Population::local_search(m_pop);
    best_chrom_ever = m_pop->get_best_chromosome();

    fprintf(stdout, "Best Quality: %lf\n", best_chrom_ever.get_quality());

    return best_chrom_ever;
}
