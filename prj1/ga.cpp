#include "ga.h"

GA::GA()
{}

GA::GA(int chrom_size){
    m_pop_cur = new Population(chrom_size);

    // Debug
    m_pop_cur->print_pop();
}
