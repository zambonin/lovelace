#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void floydWarshall(uint32_t *dists, uint32_t v) {
  uint32_t sum = 0, i, f, d;
  for (i = 0; i < v; ++i) {
    for (f = 0; f < v; ++f) {
      for (d = 0; d < v; ++d) {
        if (!__builtin_uadd_overflow(dists[f * v + i], dists[i * v + d],
                                     &sum)) {
          dists[f * v + d] =
              sum ^ ((dists[f * v + d] ^ sum) & -(dists[f * v + d] < sum));
        }
      }
    }
  }
}

void printSolution(uint32_t *dists, uint32_t v) {
  printf("All pair shortest distances\n");
  for (uint32_t i = 0; i < v; ++i) {
    for (uint32_t j = 0; j < v; ++j) {
      if (dists[i * v + j] == UINT32_MAX) {
        printf("%7s", "inf");
      } else {
        printf("%7u", dists[i * v + j]);
      }
    }
    printf("\n");
  }
}

int32_t main(int32_t argc, char **argv) {
  if (argc < 2) {
    printf("Missing input filename.\n");
    exit(EXIT_FAILURE);
  }

  FILE *input = fopen(argv[1], "r");
  if (input == NULL) {
    printf("Missing file \"%s\"\n", argv[1]);
    exit(EXIT_FAILURE);
  }

  uint32_t v, e;
  fscanf(input, "%u %u", &v, &e);

  uint32_t *dists = malloc(v * v * sizeof(uint32_t)), source, dest, cost, i;
  if (dists == NULL) {
    printf("Matrix is too big!\n");
    exit(EXIT_FAILURE);
  }
  memset(dists, UINT32_MAX, v * v * sizeof(uint32_t));

  for (i = 0; i < e; ++i) {
    fscanf(input, "%u %u %u", &source, &dest, &cost);
    if (cost < dists[source * v + dest]) {
      dists[source * v + dest] = cost;
    }
  }
  fclose(input);

  for (i = 0; i < v; ++i) {
    dists[i * v + i] = 0;
  }

  floydWarshall(dists, v);
  printSolution(dists, v);
  free(dists);
  exit(EXIT_SUCCESS);
}
