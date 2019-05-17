#include "population.h"
#include <cmath>

/*
 *  ===== Constructors =====
 */
Population::Population()
{}

Population::Population(Graph *g){
    m_graph = g;
}

Population::Population(Graph *g, int chrom_size){
    m_graph = g;

    // Initially generate chromosomes randomly.
    for(int i = 0; i < NUM_SOLUTION; i++){
        Chromosome* c = new Chromosome(m_graph, chrom_size);
        m_pop.push_back(c);
    }
    
    // Sort population by best quality.
    sort(m_pop.begin(), m_pop.end(), Chromosome::comp_by_quality);
    
    m_calculate_ham_dist();
    m_mutation_ratio = MIN_MUTATION_RATIO;
}

double Population::get_avg_quality(){
    double sum_quality = 0.0f;

    for(Chromosome* c : m_pop){
        sum_quality += c->m_quality;
    }

    return sum_quality / NUM_SOLUTION;
}

Chromosome Population::get_best_chromosome(){
    Chromosome* best_chrom = m_pop[NUM_SOLUTION-1];

    return *best_chrom;
}

double Population::get_avg_hamming_distance(){
    return m_avg_hamming_distance;
}
double Population::get_mutation_ratio(){
    return m_mutation_ratio;
}

Population* Population::evolution(Population* pop_origin){
    Population* pop_future = new Population(pop_origin->m_graph);       // Next generation
    vector<Chromosome*> offspring_list;
    vector<Chromosome*> chroms = pop_origin->m_pop;

    int replace_count = NUM_SOLUTION / 2;

    while(replace_count--){
        pair<Chromosome*, Chromosome*> selected_chroms = pop_origin->m_select();

        Chromosome* c_1 = selected_chroms.first;
        Chromosome* c_2 = selected_chroms.second;

        // Crossover
        Chromosome* offspring = Chromosome::crossover(c_1,c_2);

        // Mutation
        double mut_ratio = pop_origin->get_mutation_ratio();
        offspring = Chromosome::mutate(offspring,mut_ratio);
        offspring_list.push_back(offspring);

        // Quality calculation
        offspring->m_calculate_quality();

        // Local optimization
        offspring = Chromosome::local_search(offspring);

    }

    // Replacement
    for(int i = 0 ;i < offspring_list.size(); i++){
        chroms[i] = offspring_list[i];
    }
    
    // Sort population by best quality.
    sort(chroms.begin(), chroms.end(), Chromosome::comp_by_quality);
    pop_future->set_pop(chroms);
    pop_future->m_calculate_ham_dist();
    pop_future->m_calculate_mutation_ratio();

    return pop_future;
}

void Population::local_search(Population* pop){
    for(int i=0;i<NUM_SOLUTION;i++){
        Chromosome* c = pop->m_pop[i];

        c->m_calculate_quality();

        c = Chromosome::local_search(c);

        pop->m_pop[i] = c;
    }
    sort(pop->m_pop.begin(), pop->m_pop.end(), Chromosome::comp_by_quality);
}

pair<Chromosome*, Chromosome*> Population::m_select(){
    // Selection algorithm for GA
    
    //int random = rand() % NUM_SOLUTION;
    //Chromosome* c_1 = m_pop[random];
    //random = rand() % NUM_SOLUTION;
    //Chromosome* c_2 = m_pop[random];

    // Roulette
    //Chromosome* c_1 = m_roulette_select();
    //Chromosome* c_2 = m_roulette_select();

    // Ranking select
    Chromosome* c_1 = m_ranking_select();
    //Chromosome* c_2 = m_ranking_select();

    Chromosome* c_2;
    if(m_avg_hamming_distance < 0.1){
        // Find the farthest hamming distance    
        c_2 = m_farthest_select(c_1);
    }else{
        c_2 = m_ranking_select();
    }
    
    assert(c_1);
    assert(c_2);

    return make_pair(c_1, c_2);
}

// Roulette Selection Algorithm
Chromosome* Population::m_roulette_select(){
    double sum_fitness = m_calculate_fitness(3);

    int point = rand()%(int)(sum_fitness);

    assert(sum_fitness > point);

    double sum = 0.0f;

    for(int i=0; i< NUM_SOLUTION; i++){
        Chromosome* c = m_pop[i];
        double fitness = c->get_fitness();

        assert(fitness > 0);

        sum = sum + fitness;
        if(point < sum){
            return c;
        }
    }
    exit(-1);
}

// Ranking Selection Algorithm
Chromosome* Population::m_ranking_select(){
    double sum_fitness = m_calculate_fitness();

    int point = rand()%(int)(sum_fitness);
 
    assert(sum_fitness > point);

    double sum = 0.0f;

    for(int i=0; i< NUM_SOLUTION; i++){
        Chromosome* c = m_pop[i];
        double fitness = c->get_fitness();

        assert(fitness > 0);

        sum = sum + fitness;
        if(point < sum){
            return c;
        }
    }
    exit(-1);
}
Chromosome* Population::m_farthest_select(Chromosome* mate){
    // Find idx
    int idx = 0;
    for(int i=0;i<NUM_SOLUTION;i++){
        if(*m_pop[i]==*mate){idx = i; break;}
    }

    int max_dist = 0;
    int idx_farthest = 0;
    for(int i=0;i<NUM_SOLUTION;i++){
        if(max_dist < m_hamming_distance[idx][i]){
            max_dist = m_hamming_distance[idx][i];
            idx_farthest = i;
        }
    }
    return m_pop[idx_farthest];
}

double Population::m_calculate_fitness(int k){
    double best_quality = m_pop[NUM_SOLUTION-1]->get_quality();
    double worst_quality = m_pop[0]->get_quality();
    double sum_fitness = 0.0f;

    if(best_quality == worst_quality){
        for(int i=0;i<NUM_SOLUTION;i++){
        m_pop[i]->set_fitness(1);
        }
        return NUM_SOLUTION;
    }

    for(int i=0; i < NUM_SOLUTION; i++){
        double quality = m_pop[i]->get_quality();
        double fitness = quality - worst_quality + (best_quality - worst_quality) / (k - 1);

        m_pop[i]->set_fitness(fitness);
        sum_fitness += fitness;
    }
    return sum_fitness;
}

double Population::m_calculate_fitness(){
    double sum_fitness = 0.0f;

    for(int i=0; i < NUM_SOLUTION; i++){
        double fitness = MAX_FITNESS + (NUM_SOLUTION - i) * (MIN_FITNESS - MAX_FITNESS) / (NUM_SOLUTION - 1);

        m_pop[i]->set_fitness(fitness);
        sum_fitness += fitness;
    }
    return sum_fitness;
}

void Population::set_pop(vector<Chromosome*> pop){
    m_pop = pop;
}

void Population::print_pop(){
    for(int i = 0; i < NUM_SOLUTION; i++){
        fprintf(stdout, "Gene #%-3d : ", i+1);
        m_pop[i]->print_chrom();
        fprintf(stdout,"Quality : %lf\n",m_pop[i]->get_quality());
    }
}

bool Population::is_termination_condition(double thresold, clock_t beg, long consumed_time){

    long total_elapsed = get_consumed_msec(beg);
    
    if(total_elapsed + consumed_time < TIME_LIMIT){
        //double avg_quality = get_avg_quality();
        //double best_quality = m_pop[NUM_SOLUTION-1]->get_quality();

        //assert(best_quality > avg_quality);

        //return ((best_quality - avg_quality) / fabs(best_quality)) < thresold;

        /*double convergence_ratio = m_check_convergence();
        fprintf(stdout, "Convergence: %lf\n",convergence_ratio);

        if(convergence_ratio < 0.9){
            return false;
        }*/
        if(m_avg_hamming_distance > 0.05) return false;
    }
    return true;
}

double Population::m_check_convergence(){
    int count = 1;
    int max_count = 1;

    for(int i=1;i<m_pop.size();i++){
        if(m_pop[i-1]->get_quality() == m_pop[i]->get_quality()){
            count++;
        }
        else{
            if(max_count < count) max_count = count;
            count = 1;
        }
    }
    if(max_count < count) max_count = count;

    return (double)max_count/m_pop.size();
    
}

void Population::m_calculate_ham_dist(){
    
    // create saving box to keep hamming distances
    m_hamming_distance = new int*[NUM_SOLUTION];
    for(int i=0;i<NUM_SOLUTION;i++){
        m_hamming_distance[i] = new int[NUM_SOLUTION];
    }
    
    int n = NUM_SOLUTION;
    int sum_ham_dist = 0;

    for(int i=0;i<n-1;i++){
        for(int j=i+1;j<n;j++){
            int ham_dist = Chromosome::calculate_hamming_distance(m_pop[i],m_pop[j]);
            m_hamming_distance[i][j] = m_hamming_distance[j][i] = ham_dist;
            sum_ham_dist += ham_dist;
        }
    }

    m_avg_hamming_distance = (double)(2*sum_ham_dist) / (n*(n-1));

    // standarization
    int length = m_pop[0]->get_gene().size();
    m_avg_hamming_distance /= length;
}

void Population::m_calculate_mutation_ratio(){
    double min = MIN_MUTATION_RATIO;
    double max = MAX_MUTATION_RATIO;

    double x = m_avg_hamming_distance;
    if(x>0.5) x= 0.5;

    assert(x<=0.5);

    m_mutation_ratio = min + (max-min) * cos(x*M_PI);
}
