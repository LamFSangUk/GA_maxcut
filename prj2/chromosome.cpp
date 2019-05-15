#include "chromosome.h"

/*
 *  ===== Constructors =====
 */
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
#ifdef NORMALIZE
    // Normailize
    m_normalize();
#endif
    // Calculate the initial quality
    m_calculate_quality();
}

Chromosome::Chromosome(const Chromosome &ch){
    m_graph = ch.m_graph;
    copy(ch.m_gene.begin(), ch.m_gene.end(), back_inserter(m_gene));
    m_quality = ch.m_quality;
    m_fitness = ch.m_fitness;
}

/*
 *  ===== Algorithms for GA =====
 */

void Chromosome::m_normalize(){

    // First vtx belongs to S group
    if(m_gene[0] == 0){
        for(int i=0; i < m_gene.size(); i++){
            m_gene[i] = !m_gene[i];
        }
    }
}

Chromosome* Chromosome::crossover(Chromosome* husband, Chromosome* wife){
    // Crossover algorithm for GA
    Chromosome* offspring = new Chromosome(husband->m_graph);
    
    // - One-point crossover
    //offspring->m_one_point_crossover(husband, wife);

    // - Uniform Crossover
    offspring->m_uniform_crossover(husband, wife);
#ifdef NORMALIZE
    // Normalize
    offspring->m_normalize();
#endif
    offspring->m_calculate_quality();

    return offspring;    
}

Chromosome* Chromosome::mutate(Chromosome* chrom){
    chrom->m_typical_mutate(MUTATION_THRESHOLD);
#ifdef NORMALIZE
    chrom->m_normalize();
#endif

    chrom->m_calculate_quality();

    return chrom;
}

Chromosome* Chromosome::local_search(Chromosome* chrom){
    
    // Generate random permutation
    int * perm = new int[chrom->m_gene.size()];
    for(int i=0;i<chrom->m_gene.size();i++){
        perm[i] = i;
    }
    random_shuffle(&perm[0], &perm[chrom->m_gene.size()]);

    bool improved = true;

    while(improved){
        improved = false;
        for(int i=0; i<chrom->m_gene.size();i++){
            int variation = 0;
            if((variation = chrom->m_variation_moving_vertex(perm[i])) > 0){

                // local dim serach
                chrom->m_gene[perm[i]] = 1 - chrom->m_gene[perm[i]];

                chrom->m_quality += variation;

                int calc = chrom->m_quality;

                chrom->m_normalize();
                chrom->m_calculate_quality();
                assert(calc == chrom->m_quality);

                improved = true;
            }
        }
    }

    return chrom;
}

int Chromosome::m_variation_moving_vertex(int idx){
    int ** edges = m_graph->get_edges();
    int variation = 0;
    
    for(int i=0;i<m_gene.size();i++){
        variation += (-1 * (m_gene[idx] ^ m_gene[i]) * edges[idx+1][i+1] + (m_gene[idx]==m_gene[i]) * edges[idx+1][i+1]);
    }

    return variation;
}

void Chromosome::m_one_point_crossover(Chromosome* husband, Chromosome* wife){
    // One-point crossover
    vector<int> husband_gene = husband->get_gene();
    vector<int> wife_gene = wife->get_gene();

    int length = husband_gene.size();

    assert(length > 0);

    int crosspoint = rand() % length;

    // Get genes from father
    for(int i=0;i<crosspoint;i++){
        m_gene.push_back(husband_gene[i]);
    }
    // Get genes from mother
    for(int i=crosspoint;i<length;i++){
        m_gene.push_back(wife_gene[i]);
    }
}

void Chromosome::m_uniform_crossover(Chromosome* husband, Chromosome* wife){
     
    if(husband->get_quality() < wife->get_quality()){ // Swap only if wife has better quality than husband.
        Chromosome* temp = husband;
        husband = wife;
        wife = temp;
    }

    assert(husband->get_quality()>=wife->get_quality());

    vector<int> husband_gene = husband->get_gene();
    vector<int> wife_gene = wife->get_gene(); 

    int length = husband_gene.size();

    for(int i=0; i < length; i++){
        double random = (double)rand() / (double)RAND_MAX;

        if(random > UNIFORM_CROSSOVER_THRESHOLD)
            m_gene.push_back(wife_gene[i]);
        else
            m_gene.push_back(husband_gene[i]);
    }
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

/*
 *  ===== Getter & Setter =====
 */
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

void Chromosome::m_calculate_quality(){
    assert(m_graph);

    int ** edges = m_graph->get_edges();
    m_quality = 0.0f;

    for(int i = 0; i < m_gene.size(); i++){
        // m_gene.size is equal to num_vtx
        for(int j = i+1; j < m_gene.size(); j++){
            
            m_quality += ((m_gene[i] ^ m_gene[j]) * edges[i+1][j+1]);
        }
    }
}

// Overload
bool Chromosome::operator<(const Chromosome& c){
    if(m_quality < c.m_quality){
        return true;
    }/*else if(m_quality == c.m_quality){

        assert(m_gene.size() == c.m_gene.size());

        for(int i=0;i<m_gene.size();i++){

            if(m_gene[i] < c.m_gene[i]){
                return true;
            }else if( m_gene[i] > c.m_gene[i]){
                return false;
            }
        }
    }*/

    return false;
}

bool Chromosome::operator==(const Chromosome& c){
    return m_gene == c.m_gene;
}

bool Chromosome::comp_by_quality(Chromosome* c_1, Chromosome* c_2){
    return *c_1<*c_2;
}

void Chromosome::print_chrom(){
    for(auto gene : m_gene){
        fprintf(stdout, "%d ", gene);
    }
}
