#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

#define INFINITY_LIKE 99999

void _time(double *t) {

  static int sec = -1;
  struct timeval tv;

  gettimeofday(&tv, (struct timezone *) 0);

  if (sec < 0) {
    sec = tv.tv_sec;
  }
  *t = (tv.tv_sec - sec) + 1.0e-6 * tv.tv_usec;

}

// Solves the all-pairs shortest path problem using Floyd Warshall algorithm
void floydWarshall (uint32_t* dists, uint32_t v) {

  uint32_t sum = 0;
  double start = 0, start_loop_1 = 0, start_loop_2 = 0, start_loop_3 = 0,
         end = 0, end_loop_1 = 0, end_loop_2 = 0, end_loop_3 = 0;
  _time(&start);

  for (uint32_t i = 0; i < v; ++i) {
    _time(&start_loop_1);
    for (uint32_t f = 0; f < v; ++f) {
      _time(&start_loop_2);
      for (uint32_t d = 0; d < v; ++d) {
        _time(&start_loop_3);
        if (!__builtin_uadd_overflow(dists[f*v + i], dists[i*v + d], &sum)) {
          dists[f*v + d] = \
            sum ^ ((dists[f*v + d] ^ sum) & -(dists[f*v + d] < sum));
        }
        _time(&end_loop_3);
      }
      _time(&end_loop_2);
    }
    _time(&end_loop_1);
  }
  _time(&end);

  printf("FW: %.8f\nInner Comp. Second Loop: %.8f\n\
Inner Comp. Third Loop: %.8f\nInner Comp.: %.20f\n",
      end - start, end_loop_1 - start_loop_1,
      end_loop_2 - start_loop_2, end_loop_3 - start_loop_3);

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

    double start_prg, end_prg;
    _time(&start_prg);

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
    /* printSolution (dists, v); */

    _time(&end_prg);
    printf("Program Execution Time: %.8f\n", end_prg - start_prg);

    return 0;

}
