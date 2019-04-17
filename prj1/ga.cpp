#include "ga.h"

GA::GA()
{}

GA::GA(Graph* g, int chrom_size){
    m_graph = g;

    m_pop_cur = new Population(m_graph, chrom_size);

    // Debug
    //m_pop_cur->print_pop();
}

Chromosome GA::run(){
    // Initial seed for random
    srand(time(NULL));

    double avg_quality = m_pop_cur->get_avg_quality();
    fprintf(stdout, "1st Generation : %lf\n", avg_quality);

    Chromosome best_chrom = m_pop_cur->get_best_chromosome();

    int t=100;
    while(t--){
        fprintf(stdout,"Loop %d\n",100-t);
        m_pop_next = Population::evolution(m_pop_cur);
        avg_quality = m_pop_next->get_avg_quality();
        fprintf(stdout, "Generation : %lf\n", avg_quality);
    
        m_pop_cur = m_pop_next;

        best_chrom = m_pop_cur->get_best_chromosome();
        fprintf(stdout, "Best Chromosome : ");
        best_chrom.print_chrom();
        fprintf(stdout, "\nBest Quality : %lf\n\n",best_chrom.get_quality());

        m_pop_cur->print_pop();
    }

    return best_chrom;
}
