#include "population.h"

Population::Population()
{}

Population::Population(Graph *g, int chrom_size){
    m_graph = g;

    srand(time(NULL));

    for(int i = 0; i < NUM_SOLUTION; i++){
        Chromosome* c = new Chromosome(m_graph, chrom_size);
        m_pop.push_back(*c);
    }
}

double Population::get_avg_fitness(){
    double sum_fitness = 0.0f;

    for(Chromosome c : m_pop){
        sum_fitness += c.m_fitness;
    }

   return sum_fitness / NUM_SOLUTION;
}

void Population::print_pop(){
    for(int i = 0; i < NUM_SOLUTION; i++){
        fprintf(stdout, "Gene #%d : ", i+1);
        m_pop[i].print_chrom();
        fprintf(stdout,"\n");
    }
}
