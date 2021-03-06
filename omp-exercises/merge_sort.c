#include <omp.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SEED 26
#define TASKS 1 << 10

void merge(uint32_t *vec, uint32_t *temp, uint32_t size, uint32_t half) {
  uint32_t i1 = 0, i2 = half, it = 0;

  while (i1 < half && i2 < size) {
    temp[it++] = (vec[i1] <= vec[i2]) ? vec[i1++] : vec[i2++];
  }
  while (i1 < half) {
    temp[it++] = vec[i1++];
  }
  while (i2 < size) {
    temp[it++] = vec[i2++];
  }

  memcpy(vec, temp, size * sizeof(uint32_t));
}

void mergesort(uint32_t *vec, uint32_t *temp, uint32_t size) {
  if (size < 2) {
    return;
  }

  uint32_t half = size / 2;
#pragma omp task shared(vec) firstprivate(temp, half, size) if (size > TASKS)
  mergesort(vec, temp, half);
#pragma omp task shared(vec) firstprivate(temp, half, size) if (size > TASKS)
  mergesort(vec + half, temp + half, size - half);
#pragma omp taskwait
  merge(vec, temp, size, half);
}

int32_t main(int32_t argc, char **argv) {
  if (argc < 2) {
    printf("Usage: %s <positive number>\n", argv[0]);
    return 1;
  }

  uint32_t n = strtoul(argv[1], NULL, 0), i,
           *vector = (uint32_t *)calloc(n, sizeof(uint32_t)),
           *temp = (uint32_t *)calloc(n, sizeof(uint32_t));

  srandom(SEED);
  for (i = 0; i < n; ++i) {
    vector[i] = random();
  }

#pragma omp parallel
#pragma omp single
  mergesort(vector, temp, n);

  uint8_t correct = 1;
  for (i = 0; i < n - 1; ++i) {
    correct &= (vector[i] <= vector[i + 1]);
  }

  free(vector);
  free(temp);

  return (!correct);
}
