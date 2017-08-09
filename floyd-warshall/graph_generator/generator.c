#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

// Main program - reads parameters, generates graph
int main (int argc, char* argv[]) {

    //Checks if parameters have been passed
    if (argc < 6) {
        printf("Missing parameters.\nUsage: %s [#vertices] [#edges] [#max cost] [rand seed] [output file name]\n",argv[0]);
        exit(1);
    }

    //inputs
    uint32_t v, e, max_cost, seed;
    v = atoi(argv[1]);
    e = atoi(argv[2]);
    max_cost = atoi(argv[3]);
    if (max_cost == 0) {
        printf("Max cost must be greater than zero.\n");
        exit(1);
    }
    seed = atoi(argv[4]);
    srand(seed);

    //Tries to open the output file
    FILE* output = fopen(argv[5], "w");
    if(!output){
        printf("Could not open file \"%s\"\n",argv[5]);
        exit(1);
    }

    //Writes output file
    //First line: v (number of vertices) and e (number of edges)
    fprintf(output, "%u %u\n", v, e);

    //Generates edges to write to file
    uint32_t source, dest, cost;
    uint32_t i;
    for ( i = 0; i < e; ++i ){
        source = rand() % v;
        dest = rand() % v;
        cost = rand() % max_cost;
        fprintf(output, "%u %u %u\n", source, dest, cost);
    }

    fclose(output);

    return 0;
}
