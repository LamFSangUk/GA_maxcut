#ifndef __GA_H__
#define __GA_H__

#include "global.h"
#include "population.h"

class GA{
public:
    GA();
    GA(int);

private:
    Population* m_pop_cur;
    Population* m_pop_next;
};

#endif
