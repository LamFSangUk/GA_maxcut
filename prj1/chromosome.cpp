#include "chromosome.h"

Chromosome::Chromosome()
{}

Chromosome::Chromosome(int size){

    // Initialze the gene with random value
    for(int i = 0; i < size; i++){
        m_gene.push_back(rand() % 2);
    }
}

Chromosome* Chromosome::m_crossover(Chromosome c_1,Chromosome c_2){
}

void Chromosome::m_mutation(double mutation_rate){
}

vector<int> Chromosome::get_gene(){
    return m_gene;
}

void Chromosome::print_chrom(){
    for(auto gene : m_gene){
        fprintf(stdout, "%d ", gene);
    }
}
