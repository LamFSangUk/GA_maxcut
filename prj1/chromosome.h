#ifndef __CHROM_H__
#define __CHROM_H__

#include "global.h"

using namespace std;

class Chromosome{
public:
    Chromosome();
    Chromosome(int);

    vector<int> get_gene();

    // For Debug
    void print_chrom();

private:
    vector<int> m_gene;

    // Genetic Algorithm
    friend class Population;

    Chromosome* m_crossover(Chromosome, Chromosome);
    void m_mutation(double);


};

#endif
