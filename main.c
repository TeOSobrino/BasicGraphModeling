#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <time.h>
#include <unistd.h>
#include "linkedgraph.h"
#include "minheap.h"

int main(void){

    Graph_t* g = graphWeightedInputBuild();
    
    int size = g->vertex_num;
    int* dists = malloc(sizeof(int)*size+5);
    int* parents = malloc(sizeof(int)*size+5);

    dijkstraShortestPath(g, 0, parents, dists);

    int destination;
    scanf(" %d", &destination);
    int dist_dest = dists[destination];
    int num_vert = 2;
    while(parents[destination] != 0){
        destination = parents[destination];
        num_vert++;
    }
    int unvisited = (size - num_vert);
    int vip_cost = dist_dest*unvisited;

    int standard_cost = primMST(g);

    if(vip_cost < standard_cost){
        printf("VIP\n");
        printf("%d\n", vip_cost);
    }
    else if(standard_cost != vip_cost){
        printf("PADRAO\n");
        printf("%d\n", standard_cost);
    }
    else{
        printf("NDA\n");
        printf("%d\n", vip_cost);
    }

    free(dists);
    free(parents);
    graphDestroy(g);

    return 0;
}