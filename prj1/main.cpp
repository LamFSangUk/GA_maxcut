#include "global.h"
#include "ga.h"
#include "graph.h"

Graph* input_graph(){
    Graph* g;
    int num_vtx, num_edge;

    fscanf(stdin, "%d %d", &num_vtx, &num_edge);

    g = new Graph(num_vtx, num_edge);

    int vtx_1, vtx_2, weight;
    for(int i=0; i < num_edge; i++){
        fscanf(stdin,"%d %d %d",&vtx_1, &vtx_2, &weight);

        g->add_edge(vtx_1, vtx_2, weight);
        g->add_edge(vtx_2, vtx_1, weight);

    }

    return g;
}

int main(){

    Graph* g;

    g = input_graph();
    int chrom_size = g->get_num_vtx();
    
    GA* genetic_alg = new GA(chrom_size);

    // Test print
    int ** ge = g->get_edges();
    
    for(int i=1; i<11;i++){
        for(int j=1; j<11;j++){ 
            fprintf(stdout,"%d ",ge[i][j]);
        }
        fprintf(stdout,"\n");
    }


    return 0;
}
