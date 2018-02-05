#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void floyd_warshall(uint32_t *dists, uint32_t v) {
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

void print_solution(uint32_t *dists, uint32_t v) {
  printf("All pair shortest distances\n");
  for (uint32_t i = 0; i < v; ++i) {
    for (uint32_t j = 0; j < v; ++j) {
      if ((int)dists[i * v + j] < 0) {
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
    return 1;
  }

  FILE *input = fopen(argv[1], "re");
  if (input == NULL) {
    printf("Missing file \"%s\"\n", argv[1]);
    return 1;
  }

  uint32_t v, e;
  fscanf(input, "%u %u", &v, &e);

  uint32_t *dists = malloc(v * v * sizeof(uint32_t)), source, dest, cost, i;
  if (dists == NULL) {
    printf("Matrix is too big!\n");
    return 1;
  }
  memset(dists, UINT32_MAX - 1, v * v * sizeof(uint32_t));

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

  floyd_warshall(dists, v);
  print_solution(dists, v);
  free(dists);
  return 0;
}
