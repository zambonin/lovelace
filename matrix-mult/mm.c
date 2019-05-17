#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int32_t main(int32_t argc, char **argv) {
  if (argc < 2) {
    printf("Usage: %s <sq. matrix side>\n", argv[0]);
    return 1;
  }

  uint16_t size_power = strtol(argv[1], NULL, 0);
  size_t side = 1u << size_power;
  float *A = calloc(side * side, sizeof(float)),
        *B = calloc(side * side, sizeof(float)),
        *C = calloc(side * side, sizeof(float));

  if (C == NULL) {
    free(A);
    free(B);
    printf("Matrices are too big!");
    return 1;
  }

  size_t i, j, k, jj, kk;
  for (i = 0; i < side; ++i) {
    for (j = 0; j < side; ++j) {
      A[i * side + j] = 1.0;
      B[i * side + j] = 2.0;
      C[i * side + j] = 0.0;
    }
  }

  for (jj = 0; jj < side; jj += MSTEP) {
    for (kk = 0; kk < side; kk += MSTEP) {
      for (i = 0; i < side; ++i) {
        for (j = jj; j < jj + MSTEP; ++j) {
          float r = 0.0;
          for (k = kk; k < kk + MSTEP; ++k) {
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
