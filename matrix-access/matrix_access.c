#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static inline uint64_t row_index(uint64_t k, uint32_t r, uint32_t c) {
  return k + (r + c) * 0;
}
static inline uint64_t col_index(uint64_t k, uint32_t r, uint32_t c) {
  return (k / (c - 1)) + (k % r) * c;
}

int32_t main(int32_t argc, char **argv) {
  int8_t debug = 0, c;
  char *rvalue = "100", *cvalue = "100";
  uint64_t (*index)(uint64_t, uint32_t, uint32_t) = &row_index;

  while ((c = getopt(argc, argv, "hadr:c:")) != -1) {
    switch (c) {
    case 'a':
      index = &col_index;
      break;
    case 'd':
      debug = 1;
      break;
    case 'r':
      rvalue = optarg;
      break;
    case 'c':
      cvalue = optarg;
      break;
    case 'h':
      printf("Usage: %s\n", argv[0]);
      printf("  -h\tShow this message\n");
      printf("  -a\tAccesses the matrix by column\n");
      printf("  -d\tPrints debug information\n");
      printf("  -c n\tNumber of columns for the matrix (default = 100)\n");
      printf("  -r n\tNumber of rows for the matrix (default = 100)\n");
      return 0;
    default:
      return 1;
    }
  }

  uint32_t row = strtol(rvalue, NULL, 0), col = strtol(cvalue, NULL, 0);
  uint32_t *matrix = calloc((uint64_t)row * col, sizeof(uint32_t)), order = 0;

  if (matrix == NULL) {
    printf("Matrix is too big!\n");
    return 1;
  }

  if (debug == 1) {
    printf("Allocated data structure: matrix[%d][%d]\n", row, col);
    printf("Memory access starts!\n");
  }

  for (uint64_t i = 0; i < (uint64_t)row * col; ++i) {
    matrix[index(i, row, col)] = order++;
  }

  if (debug == 1) {
    printf("Order that matrix cells were accessed:\n");
    for (uint32_t i = 0; i < row; i++) {
      for (uint32_t j = 0; j < col; j++) {
        printf("matrix[%d][%d] = %d\n", i, j, matrix[i * col + j]);
      }
    }
    printf("Memory access ends!\n");
  }

  free(matrix);
  return 0;
}
