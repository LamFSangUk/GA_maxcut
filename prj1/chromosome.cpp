#include "chromosome.h"

Chromosome::Chromosome()
{}

Chromosome::Chromosome(Graph* g, int size){
    m_graph = g;

    // Initialze the gene with random value
    for(int i = 0; i < size; i++){
        m_gene.push_back(rand() % 2);
    }

    // Calculate the initial fitness
    m_calculate_fitness();
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

void Chromosome::m_calculate_fitness(){
    int ** edges = m_graph->get_edges();
    m_fitness = 0.0f;

    for(int i = 0; i < m_gene.size(); i++){
        // m_gene.size is equal to num_vtx
        for(int j = 0; j < m_gene.size(); j++){
            
            m_fitness += (m_gene[i] * (m_gene[i] ^ m_gene[j]) * edges[i+1][j+1]);
        }
    }
}
