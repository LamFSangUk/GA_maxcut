#include "graph.h"

Graph::Graph()
{}

Graph::Graph(int num_vtx, int num_edge){
    m_num_vtx = num_vtx;
    m_num_edge = num_edge;

    m_edges = new int*[m_num_vtx + 1];
    for(int i=0; i < m_num_vtx + 1; i++){
        m_edges[i]= new int[m_num_vtx + 1];
    }
}

void Graph::add_edge(int start, int end, int weight){
    m_edges[start][end] = weight;
}

int** Graph::get_edges(){
    return m_edges;
}

int Graph::get_num_vtx(){
    return m_num_vtx;
}
