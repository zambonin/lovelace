#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define INFINITY_LIKE 99999

// Solves the all-pairs shortest path problem using Floyd Warshall algorithm
void floydWarshall (uint32_t* dists, uint32_t v) {
    //TODO

}

/* A utility function to print solution */
void printSolution (uint32_t* dists, uint32_t v) {
    uint32_t i, j;

    printf ("All pair shortest distances\n");
    for (i = 0; i < v; ++i) {
        for (j = 0; j < v; ++j) {
            if (dists[i*v+j] > INFINITY_LIKE) printf("%7s", "inf");
            else printf ("%7u", dists[i*v+j]);
        }
        printf("\n");
    }
}

// Main program - reads input, calls FW, shows output
int main (int argc, char* argv[]) {

    //Checks if filename has been passed
    if (argc < 2) {
        printf("Missing input filename.\n");
        exit(1);
    }

    //Tries to open the input file
    FILE* input = fopen(argv[1], "r");
    if(!input){
        printf("Missing file \"%s\"\n",argv[1]);
        exit(1);
    }

    //Reads input file
    //First line: v (number of vertices) and e (number of edges)
    uint32_t v, e;
    fscanf(input, "%u %u", &v, &e);

    //Allocates distances matrix (w/ size v*v) i
    //and sets it with max distance and 0 for own vertex
    uint32_t* dists = malloc(v*v*sizeof(uint32_t));
    memset(dists, UINT32_MAX, v*v*sizeof(uint32_t));
    uint32_t i;
    for ( i = 0; i < v; ++i ) dists[i*v+i] = 0;

    //Reads edges from file and sets them in the distance matrix
    uint32_t source, dest, cost;
    for ( i = 0; i < e; ++i ){
        fscanf(input, "%u %u %u", &source, &dest, &cost);
        if (cost < dists[source*v+dest]) dists[source*v+dest] = cost;
    }

    fclose(input);

    //Computes the solution
    floydWarshall( dists, v );

    //Prints the solution
    printSolution (dists, v);

    return 0;
}
