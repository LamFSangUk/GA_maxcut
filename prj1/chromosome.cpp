#include "chromosome.h"

Chromosome::Chromosome()
{}

Chromosome::Chromosome(Graph *g){
    m_graph = g;
}

Chromosome::Chromosome(Graph* g, int size){
    m_graph = g;

    // Initialze the gene with random value
    for(int i = 0; i < size; i++){
        m_gene.push_back(rand() % 2);
    }

    // Calculate the initial quality
    m_calculate_quality();
}

Chromosome* Chromosome::crossover(Chromosome* husband, Chromosome* wife){
    // Crossover algorithm for GA
    Chromosome* offspring = new Chromosome(husband->m_graph);
    
    offspring->m_one_point_crossover(husband, wife);
    //offspring->m_gene.insert(offspring->m_gene.end(), husband->m_gene.begin(), husband->m_gene.begin());
    //for(int i=0;i<husband->m_gene.size();i++){

    //offspring->m_gene.push_back(husband->m_gene[i]);
    //}
    //printf("husband\t : ");husband->print_chrom();printf("\n");
    //printf("wife\t : ");    wife->print_chrom(); printf("\n");
    //printf("offspring: ");offspring->print_chrom();printf("\n");

    offspring->m_calculate_quality();

    return offspring;    
}

void Chromosome::m_one_point_crossover(Chromosome* husband, Chromosome* wife){
    // One-point crossover
    vector<int> husband_gene = husband->get_gene();
    vector<int> wife_gene = wife->get_gene();

    int length = husband_gene.size();

    assert(length > 0);

    int crosspoint = rand() % length;

    for(int i=0;i<crosspoint;i++){
        m_gene.push_back(husband_gene[i]);
        //m_gene.insert(m_gene.end(), husband_gene.begin(), husband_gene.end());
    }
    for(int i=crosspoint;i<length;i++){
        m_gene.push_back(wife_gene[i]);
    }
    //m_gene.insert(m_gene.end(), husband_gene.begin(), husband_gene.begin() + crosspoint);    
    //m_gene.insert(m_gene.end(), wife_gene.begin() + crosspoint, wife_gene.end());
}

void Chromosome::m_mutate(double mutation_threshold){
    // Mutation algorithm for GA
    m_typical_mutate(mutation_threshold);

    m_calculate_quality();
}

void Chromosome::m_typical_mutate(double mutation_threshold){
    int length = m_gene.size();
    
    for(int i = 0; i < length; i++){
        double random = ((double)rand()/(double)RAND_MAX);

        if(random < mutation_threshold){
            // Mutate
            m_gene[i] = !m_gene[i];
        }
    }
}

vector<int> Chromosome::get_gene(){
    return m_gene;
}

double Chromosome::get_quality(){
    return m_quality;
}

void Chromosome::set_fitness(double fitness){
    m_fitness = fitness;
}

double Chromosome::get_fitness(){
    return m_fitness;
}

void Chromosome::print_chrom(){
    for(auto gene : m_gene){
        fprintf(stdout, "%d ", gene);
    }
}

void Chromosome::m_calculate_quality(){
    assert(m_graph);

    int ** edges = m_graph->get_edges();
    m_quality = 0.0f;

    for(int i = 0; i < m_gene.size(); i++){
        // m_gene.size is equal to num_vtx
        for(int j = 0; j < m_gene.size(); j++){
            
            m_quality += (m_gene[i] * (m_gene[i] ^ m_gene[j]) * edges[i+1][j+1]);
        }
    }
}

// Overload
bool Chromosome::operator<(const Chromosome& c){
    if(m_quality < c.m_quality){
        return true;
    }

    return false;
}

bool Chromosome::comp_by_quality(Chromosome* c_1, Chromosome* c_2){
    return *c_1<*c_2;
}
