#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int32_t main(int32_t argc, char **argv) {
  if (argc < 2) {
    printf("Usage: %s <natural non-negative number>\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  uint32_t size = strtol(argv[1], NULL, 0), i, left, right;
  uint8_t *rand_numbers = (uint8_t *)malloc(size * sizeof(uint8_t));

  for (i = 0; i < size; ++i) {
    rand_numbers[i] = random() % 100;
  }

  for (i = 0; i < size; ++i) {
    left = rand_numbers[(i + 1) % size];
    right = rand_numbers[(size + i - 1) % size];
    printf("[%d] rand = %d\t sum with neighbors = %d\n", i, rand_numbers[i],
           rand_numbers[i] + left + right);
  }

  free(rand_numbers);

  exit(EXIT_SUCCESS);
}
