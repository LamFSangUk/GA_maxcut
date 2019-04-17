#include "graph.h"

/*
 *  ===== Constructors =====
 */
Graph::Graph()
{}

Graph::Graph(int num_vtx, int num_edge){
    m_min_weight    = INT_MAX;
    m_num_edge      = num_edge;
    m_num_vtx       = num_vtx;

    // Create an adjacency matrix for graph
    m_edges = new int*[m_num_vtx + 1];
    for(int i=0; i < m_num_vtx + 1; i++){
        m_edges[i]= new int[m_num_vtx + 1];
    }
}

void Graph::add_edge(int start, int end, int weight){
    if(weight < m_min_weight) m_min_weight = weight;
    m_edges[start][end] = weight;
}

/*
 *  ===== Getter & Setter =====
 */

int** Graph::get_edges(){
    return m_edges;
}

int Graph::get_min_weight(){
    return m_min_weight;
}

int Graph::get_num_vtx(){
    return m_num_vtx;
}
