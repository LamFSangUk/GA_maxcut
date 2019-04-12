#ifndef __GRAPH_H__
#define __GRAPH_H__

#include <string.h>
#include "global.h"

#define MAX_VTX     500
#define MAX_EDGE    5000

class Graph{
public:
    Graph();
    Graph(int, int);
    void add_edge(int, int, int);

    // for debug
    int** get_edges();
    int get_num_vtx();

private:
    int m_num_vtx;
    int m_num_edge;
    int ** m_edges; // Adjacency Matrix
};

#endif
