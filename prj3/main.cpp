#include "global.h"
#include "ga.h"
//#include "ls.h"
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

/*
 * Print the best solution.
 * The result will be translate from chromosome to subgroup of graph.
 */
void print_result(Chromosome best_result){
    vector<bool> genes = best_result.get_gene();

    int vtx_num = 1;
    for(bool gene : genes){
        if(gene){
            fprintf(stdout, "%d ", vtx_num);
        }
        vtx_num++;
    }
}

int main(){

    Graph* g;

    g = input_graph();
    int chrom_size = g->get_num_vtx();

    GA* genetic_alg = new GA(g, chrom_size);
    //LS* ls = new LS(g, chrom_size);

    Chromosome best_chrom = genetic_alg->run();
    //Chromosome best_chrom = ls->run();

    print_result(best_chrom);

    return 0;
}
