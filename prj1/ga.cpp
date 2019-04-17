#include "ga.h"

GA::GA()
{}

GA::GA(Graph* g, int chrom_size){
    m_graph = g;

    m_pop_cur = new Population(m_graph, chrom_size);

    m_convergence_threshold = THRESHOLD_CONVERGENCE;

    // Debug
    //m_pop_cur->print_pop();
}

Chromosome GA::run(){
    // Initial seed for random
    srand(time(NULL));

    Chromosome best_chrom;
    clock_t beg = start_tick();
    long consumed_msec = 0;
    int t=1;
    while(!m_pop_cur->is_termination_condition(m_convergence_threshold, beg, consumed_msec)){
    
        // One loop of genetic algorithm
        clock_t loop_beg = start_tick();
        m_pop_next = Population::evolution(m_pop_cur);
                m_pop_cur = m_pop_next;

#ifndef NDEBUG

        double avg_quality = m_pop_cur->get_avg_quality();
        
        avg_quality = m_pop_next->get_avg_quality();
        fprintf(stdout, "Generation #%5d\n Avg  Quality : %lf\n",t++,avg_quality);

        best_chrom = m_pop_cur->get_best_chromosome();
        fprintf(stdout, "Best Quality : %lf\n",best_chrom.get_quality());
        fprintf(stdout, "Best Chromosome : "); best_chrom.print_chrom();
        fprintf(stdout, "\n");

        m_pop_cur->print_pop();
        fprintf(stdout, "\n\n");
#endif
        consumed_msec = get_consumed_msec(loop_beg);
    }

    best_chrom = m_pop_cur->get_best_chromosome();

    return best_chrom;
}
