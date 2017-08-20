#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void usage();

#define COLUMNS 100
#define ROWS 100

#define INPUT_FAILURE (-1)
#define OK 0

#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif

int main(int argc, char *argv[]) {
  int *matrix;
  int rows = ROWS;
  int columns = COLUMNS;
  int byrow = TRUE;
  int debug = FALSE;
  int order = 0;

  int i, j, opt;

  argc--;
  argv++;
  while (argc >= 1) {
    opt = 1;
    if (*argv[0] == '-') {
      if ((strcmp(argv[0], "-h") == 0) || (strcmp(argv[0], "--help") == 0)) {
        usage();
        exit(OK);
      } else if ((strcmp(argv[0], "-d") == 0) ||
                 (strcmp(argv[0], "--debug") == 0)) {
        debug = TRUE;
      } else if (strcmp(argv[0], "-bycolumn") == 0) {
        byrow = FALSE;
      } else if (strcmp(argv[0], "-byrow") == 0) {
        byrow = TRUE;
      } else {
        opt = 2;
        if (argc < 2) {
          usage();
          exit(INPUT_FAILURE);
        } else if ((strcmp(argv[0], "-c") == 0) ||
                   (strcmp(argv[0], "--columns") == 0)) {
          columns = atoi(argv[1]);
          if (columns < 1) {
            printf("Number of columns cannot be smaller than one. Input: %d\n",
                   columns);
            exit(INPUT_FAILURE);
          }
        } else if ((strcmp(argv[0], "-r") == 0) ||
                   (strcmp(argv[0], "--rows") == 0)) {
          rows = atoi(argv[1]);
          if (rows < 1) {
            printf("Number of rows cannot be smaller than one. Input: %d\n",
                   rows);
            exit(INPUT_FAILURE);
          }
        } else {
          usage();
          exit(INPUT_FAILURE);
        }
      }
    }
    argc -= opt;
    argv += opt;
  }

  assert(columns > 0 && rows > 0);

  matrix = malloc(sizeof(int) * columns * rows);
  assert(matrix != NULL);
  printf("Allocated data structure: matrix[%d][%d]\n", rows, columns);

  printf("Memory access starts!\n");
  if (byrow != 0) {
    for (i = 0; i < rows; i++) {
      for (j = 0; j < columns; j++) {
        matrix[i * columns + j] = order;
        order++;
      }
    }
  } else {
    for (j = 0; j < columns; j++) {
      for (i = 0; i < rows; i++) {
        matrix[i * columns + j] = order;
        order++;
      }
    }
  }

  if (debug != 0) {
    printf("Order that matrix cells were accessed\n");
    for (i = 0; i < rows; i++) {
      for (j = 0; j < columns; j++) {
        printf("matrix[%d][%d] = %d\n", i, j, matrix[i * columns + j]);
      }
    }
  }
  printf("Memory access ends!\n");

  free(matrix);

  return 0;
}

void usage() {
  printf("Usage options\n");
  printf("  -h --help            Prints this message\n");
  printf("  -d --debug           Prints debug information\n");
  printf("  -c --columns         Sets the number of columns of the matrix "
         "(default value = %d)\n",
         COLUMNS);
  printf("  -r --rows            Sets the number of rows of the matrix "
         "(default value = %d)\n",
         ROWS);
  printf("  -bycolumn            Accesses the matrix by column\n");
  printf("  -byrow               Accesses the matrix by row (default)\n");
  printf("\n");
}
