#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define SEED 26

uint32_t apply(char operator, uint32_t a, uint32_t b) {
  switch (operator) {
  case '+':
    return a + b;
  case '-':
    return a - b;
  case '*':
    return a * b;
  case '^':
    return a ^ b;
  default:
    return 0;
  }
}

void scan(uint8_t *vec, uint32_t *result, uint64_t size, char operator) {
  result[0] = vec[0];
  for (uint64_t i = 1; i < size; ++i) {
    result[i] = apply(operator, result[i - 1], vec[i]);
  }
}

int32_t main(int32_t argc, char **argv) {
  if (argc < 3) {
    printf("Usage: %s <positive number> [+-*^]\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  uint64_t i = 0, n = strtoul(argv[1], NULL, 0);
  uint8_t *vec = (uint8_t *)malloc(n * sizeof(uint8_t));
  uint32_t *res = (uint32_t *)malloc(n * sizeof(uint32_t));

  srandom(SEED);
  for (i = 0; i < n; i++) {
    vec[i] = (random() % 5) + 1;
  }

  scan(vec, res, n, argv[2][0]);

  for (i = 0; i < n; ++i) {
    printf("%d ", res[i]);
  }
  printf("\n");

  free(vec);
  free(res);

  exit(EXIT_SUCCESS);
}
