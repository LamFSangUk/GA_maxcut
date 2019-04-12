#include "population.h"

Population::Population()
{}

Population::Population(int chrom_size){

    srand(time(NULL));

    for(int i = 0; i < NUM_SOLUTION; i++){
        Chromosome* c = new Chromosome(chrom_size);
        m_pop.push_back(*c);
    }
}

void Population::print_pop(){
    for(int i = 0; i < NUM_SOLUTION; i++){
        m_pop[i].print_chrom();
        fprintf(stdout,"\n");
    }
}
