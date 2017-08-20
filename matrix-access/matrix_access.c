#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  int byrow = 1, debug = 0, c;
  char *rvalue = "100", *cvalue = "100";

  while ((c = getopt(argc, argv, "hadr:c:")) != -1) {
    switch (c) {
    case 'a':
      byrow = 0;
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

  int row = strtol(rvalue, NULL, 0), col = strtol(cvalue, NULL, 0);
  int *matrix = malloc(row * col * sizeof(int)), order = 0;

  if (matrix == NULL) {
    printf("Matrix is too big!\n");
    return 1;
  }

  if (debug == 1) {
    printf("Allocated data structure: matrix[%d][%d]\n", row, col);
    printf("Memory access starts!\n");
  }

  if (byrow == 1) {
    for (int i = 0; i < row; ++i) {
      for (int j = 0; j < col; ++j) {
        matrix[i * col + j] = order++;
      }
    }
  } else {
    for (int j = 0; j < col; ++j) {
      for (int i = 0; i < row; ++i) {
        matrix[i * col + j] = order++;
      }
    }
  }

  if (debug == 1) {
    printf("Order that matrix cells were accessed:\n");
    for (int i = 0; i < row; i++) {
      for (int j = 0; j < col; j++) {
        printf("matrix[%d][%d] = %d\n", i, j, matrix[i * col + j]);
      }
    }
    printf("Memory access ends!\n");
  }

  free(matrix);
  return 0;
}
