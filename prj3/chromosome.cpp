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

    // Calculate the initial quality
    m_calculate_quality();
}

Chromosome::Chromosome(const Chromosome &ch){
    m_graph = ch.m_graph;
    copy(ch.m_gene.begin(), ch.m_gene.end(), back_inserter(m_gene));
    m_quality = ch.m_quality;
    m_fitness = ch.m_fitness;
}

Chromosome::~Chromosome(){
  m_gene.clear();
  m_gene.shrink_to_fit();
}

/*
 *  ===== Algorithms for GA =====
 */

void Chromosome::m_normalize(Chromosome* c){

    int ham_dist = Chromosome::calculate_hamming_distance(this,c);
    int max_dist = m_gene.size();
    if(ham_dist > (max_dist / 2)){

        // Flip all bits
        for(int i=0; i < max_dist; i++){
            m_gene[i] = !m_gene[i];
        }
    }
}

Chromosome* Chromosome::crossover(Chromosome* husband, Chromosome* wife){
    // Crossover algorithm for GA
    Chromosome* offspring = new Chromosome(husband->m_graph);

#ifdef NORMALIZE
    // Normalize
    wife->m_normalize(husband);
#endif

    // - One-point crossover
    //offspring->m_one_point_crossover(husband, wife);


    // - Uniform Crossover
    offspring->m_uniform_crossover(husband, wife);


    return offspring;
}

Chromosome* Chromosome::mutate(Chromosome* chrom, double mutation_ratio = MUTATION_THRESHOLD){
    chrom->m_typical_mutate(mutation_ratio);

    return chrom;
}

int Chromosome::calculate_hamming_distance(Chromosome* c1, Chromosome*c2){
    int size = c1->m_gene.size();
    int ham_dist = 0;
    for(int i = 0; i < size; i++){
        ham_dist += (c1->m_gene[i] ^ c2->m_gene[i]);

    }

    return ham_dist;
}

int Chromosome::m_variation_moving_vertex(int idx){
    int ** edges = m_graph->get_edges();
    int variation = 0;

    int size = m_gene.size();
    for(int i = 0; i < size; i++){
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
 *  ===== Algorithms for Local Search =====
 */

Chromosome* Chromosome::local_search(Chromosome* chrom){

    //chrom->m_one_bit_flip_local_search(chrom);
    chrom->m_fiduccia_mattheyses(chrom);

    return chrom;
}

void Chromosome::m_one_bit_flip_local_search(Chromosome* chrom){
    // Generate random permutation
    int size = chrom->m_gene.size();
    int * perm = new int[size];
    for(int i=0;i<size;i++){
        perm[i] = i;
    }
    random_shuffle(&perm[0], &perm[size]);

    bool improved = true;

    while(improved){
        improved = false;
        for(int i=0; i<size;i++){
            int variation = 0;
            if((variation = chrom->m_variation_moving_vertex(perm[i])) > 0){

                // local dim serach
                chrom->m_gene[perm[i]] = 1 - chrom->m_gene[perm[i]];

                chrom->m_quality += variation;

                //int calc = chrom->m_quality;

                //chrom->m_calculate_quality();
                //assert(calc == chrom->m_quality);

                improved = true;
            }
        }
    }

    delete [] perm;
}

void Chromosome::m_fiduccia_mattheyses(Chromosome* chrom){
    int ** edges = chrom->m_graph->get_edges();
    vector<int>& gene = chrom->m_gene;
    int size = chrom->m_gene.size();

    vector<int> gains(size);
    vector<bool> locks(size);
    vector<int> order(size);

    bool improved;
    do{
        improved = false;

        for(int i = 0; i < size; i++){
            // Find connected vertex from i
            int gain = 0;
            for(int j = 0; j < size; j++){
                int weight = edges[i+1][j+1];
                if(weight == 0) continue; // Not connected
                if(gene[i] ^ gene[j]) gain -= weight;
                else gain += weight;
            }
            gains[i] = gain;
            locks[i] = false;
        }

        for(int i = 0; i < size - 1; i++){
            // Find max gain
            int max_idx = 0;
            int max = INT_MIN;
            for(int j = 0; j < size; j++){
                if(locks[j]) continue;
                if(max < gains[j]){
                    max = gains[j];
                    max_idx = j;
                }
            }
            locks[max_idx] = true;

            for(int j = 0; j < size; j++){
                int weight = edges[max_idx+1][j+1];
                if(weight == 0) continue; // Not connected

                if(!locks[j]){
                  if(gene[max_idx] ^ gene[j]) gains[j] += (2 * weight);
                  else gains[j] -= (2 * weight);

                }
            }
            order[i] = max_idx;
        }

        int max_idx = 0;
        for(int i = 1; i < size - 1; i++){
            gains[order[i]] += gains[order[i-1]];
            if(gains[order[i]] >= gains[order[max_idx]]) max_idx = i;
        }
        if(gains[order[max_idx]] > 0){
            improved = true;
            for(int i = 0; i <= max_idx; i++){
                gene[order[i]] = 1 - gene[order[i]];
            }
            chrom->m_quality += gains[order[max_idx]];
        }
    }while(improved);
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

    int size =  m_gene.size();
    for(int i = 0; i < size; i++){
        // m_gene.size is equal to num_vtx
        for(int j = i+1; j < size; j++){

            m_quality += ((m_gene[i] ^ m_gene[j]) * edges[i+1][j+1]);
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
