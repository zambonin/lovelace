#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("Usage: %s <sq. matrix side>\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  uint32_t size_power = strtol(argv[1], NULL, 0);
  size_t side = (size_t)(1 << size_power);
  float *A = malloc(side * side * sizeof(float)),
        *B = malloc(side * side * sizeof(float)),
        *C = malloc(side * side * sizeof(float));

  if (A == NULL || B == NULL || C == NULL) {
    printf("Matrices are too big!");
    exit(EXIT_FAILURE);
  }

  size_t i, j, k, jj, kk;
  for (i = 0; i < side; ++i) {
    for (j = 0; j < side; ++j) {
      A[i * side + j] = 1.0;
      B[i * side + j] = 2.0;
      C[i * side + j] = 0.0;
    }
  }

  for (jj = 0; jj < side; jj += STEP) {
    for (kk = 0; kk < side; kk += STEP) {
      for (i = 0; i < side; ++i) {
        for (j = jj; j < jj + STEP; ++j) {
          float r = 0.0;
          for (k = kk; k < kk + STEP; ++k) {
            r += A[i * side + k] * B[k * side + j];
          }
          C[i * side + j] += r;
        }
      }
    }
  }

  free(A);
  free(B);
  free(C);

  return 0;
}
