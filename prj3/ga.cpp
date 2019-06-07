#include "ga.h"

GA::GA()
{}

GA::GA(Graph* g, int chrom_size){
    m_graph = g;

    clock_t beg = start_tick();
    m_beg_tick = beg;

    m_pop_cur = new Population(m_graph, chrom_size);

    m_convergence_threshold = THRESHOLD_CONVERGENCE;
}

Chromosome GA::run(){
    // Initial seed for random
    srand(time(NULL));

    Chromosome best_chrom_ever;
    int t=1;
    while(!m_pop_cur->is_termination_condition(m_beg_tick)){

        // One loop of genetic algorithm
        m_pop_next = Population::evolution(m_pop_cur);

        m_pop_cur = m_pop_next;

        Chromosome best_chrom = m_pop_cur->get_best_chromosome();
        if(t==1) best_chrom_ever = best_chrom;
        else if(best_chrom_ever.get_quality() < best_chrom.get_quality()){
            best_chrom_ever = best_chrom;
        }
#ifdef EXPERIMENT

        double avg_quality = m_pop_cur->get_avg_quality();
        double avg_ham_dist = m_pop_cur->get_avg_hamming_distance();

        avg_quality = m_pop_next->get_avg_quality();
        fprintf(stdout, "Generation #%5d\nAvg  Quality : %lf\n",t,avg_quality);

        fprintf(stdout, "Avg Hamming Dist: %lf\n",avg_ham_dist);
        fprintf(stdout, "Global Best: %lf\n",best_chrom_ever.get_quality());
        fprintf(stdout, "Best Quality : %lf\n",best_chrom.get_quality());
        fprintf(stdout, "Best Chromosome : "); best_chrom.print_chrom();

#ifdef DETAIL
        fprintf(stdout, "\n");
        m_pop_cur->print_pop();
#endif

        fprintf(stdout, "\n\n");
#endif
        t++;
    }

    return best_chrom_ever;
}
