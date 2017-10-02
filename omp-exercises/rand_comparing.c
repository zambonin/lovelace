#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define SEED 26

int32_t main(int32_t argc, char **argv) {
  if (argc < 2) {
    printf("Usage: %s <positive number>\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  uint64_t i = 0, n = strtoul(argv[1], NULL, 0), result = 0;
  srandom(SEED);

  int r1, r2;
  while (i++ < n) {
    r1 = random() % 100;
    r2 = random() % 100;
    result += (r1 < r2);
  }

  printf("random() %% 100 < random() %% 100 %ld times\n", result);
  exit(EXIT_SUCCESS);
}
