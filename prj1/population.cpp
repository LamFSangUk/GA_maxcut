#include "population.h"
#include <cmath>

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

Population* Population::evolution(Population* pop_origin){
    Population* pop_future = new Population(pop_origin->m_graph);       // Next generation
    vector<Chromosome*> offspring_list;
    vector<Chromosome*> chroms = pop_origin->m_pop;

    int replace_count = NUM_SOLUTION / 2;

    while(replace_count--){
        pair<Chromosome*, Chromosome*> selected_chroms = pop_origin->m_select();

        Chromosome* c_1 = selected_chroms.first;
        Chromosome* c_2 = selected_chroms.second;

        Chromosome* offspring = Chromosome::crossover(c_1,c_2);
        offspring->m_mutate(0.01);
        offspring_list.push_back(offspring);
    }

    // Replacement
    for(int i = 0 ;i < offspring_list.size(); i++){
        chroms[i] = offspring_list[i];
#ifndef NDEBUG
        printf("chroms#%d: ",i); chroms[i]->print_chrom(); printf("\n");
#endif
    }
    
    // Sort population by best quality.
    sort(chroms.begin(), chroms.end(), Chromosome::comp_by_quality);
    pop_future->set_pop(chroms);

    return pop_future;
}

pair<Chromosome*, Chromosome*> Population::m_select(){
    // Selection algorithm for GA
    
    //int random = rand() % NUM_SOLUTION;
    //Chromosome* c_1 = m_pop[random];
    //random = rand() % NUM_SOLUTION;
    //Chromosome* c_2 = m_pop[random];

    // Roulette
    Chromosome* c_1 = m_roulette_select();
    Chromosome* c_2 = m_roulette_select();
    
    assert(c_1);
    assert(c_2);

    return make_pair(c_1, c_2);
}

// Roulette Selection Algorithm
Chromosome* Population::m_roulette_select(){
    double sum_fitness = m_calculate_fitness(3);
#ifndef NDEBUG
    printf("sum_fitness:%lf\n",sum_fitness);
#endif
    int point = rand()%(int)(sum_fitness);

    assert(sum_fitness > point);

//    printf("point: %d\n",point);
    
    double sum = 0.0f;

    for(int i=0; i< NUM_SOLUTION; i++){
        Chromosome* c = m_pop[i];
        double fitness = c->get_fitness();

        assert(fitness > 0);

        sum = sum + fitness;
        //sum = sum + (fitness > 0 ? fitness : 0);
//        printf("point: %d sum : %lf fitness: %lf\n",point,sum,c->get_fitness());
        if(point < sum){
//            printf("select : "); c->print_chrom(); printf("\n");
            return c;
        }
    }
//    printf("here Don't");
    exit(-1);
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
        double avg_quality = get_avg_quality();
        double best_quality = m_pop[NUM_SOLUTION-1]->get_quality();

        assert(best_quality > avg_quality);

        return ((best_quality - avg_quality) / fabs(best_quality)) < thresold;
    }
    return true;
}
