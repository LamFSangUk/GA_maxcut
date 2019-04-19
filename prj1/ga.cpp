#include "ga.h"

GA::GA()
{}

GA::GA(Graph* g, int chrom_size){
    m_graph = g;

    m_pop_cur = new Population(m_graph, chrom_size);

    m_convergence_threshold = THRESHOLD_CONVERGENCE;
}

Chromosome GA::run(){
    // Initial seed for random
    srand(time(NULL));

    Chromosome best_chrom_ever;
    clock_t beg = start_tick();
    long consumed_msec = 0;
    int t=1;
    while(!m_pop_cur->is_termination_condition(m_convergence_threshold, beg, consumed_msec)){
    
        // One loop of genetic algorithm
        clock_t loop_beg = start_tick();
        m_pop_next = Population::evolution(m_pop_cur);
        
        m_pop_cur = m_pop_next;

        Chromosome best_chrom = m_pop_cur->get_best_chromosome();
        if(t==1) best_chrom_ever = best_chrom;
        else if(best_chrom_ever.get_quality() < best_chrom.get_quality()){
            best_chrom_ever = best_chrom;
        }
#ifdef EXPERIMENT

        double avg_quality = m_pop_cur->get_avg_quality();
        
        avg_quality = m_pop_next->get_avg_quality();
        fprintf(stdout, "Generation #%5d\nAvg  Quality : %lf\n",t++,avg_quality);

        fprintf(stdout, "Best Quality : %lf\n",best_chrom.get_quality());
        fprintf(stdout, "Best Chromosome : "); best_chrom.print_chrom();

#ifdef DETAIL
        fprintf(stdout, "\n");
        m_pop_cur->print_pop();
#endif

        fprintf(stdout, "\n\n");
#endif
        consumed_msec = get_consumed_msec(loop_beg);
    }
    
    return best_chrom_ever;
}
