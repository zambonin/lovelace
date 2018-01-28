#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

uint32_t smith_waterman(const char *seq1, const char *seq2) {
  int32_t len1 = strlen(seq1), len2 = strlen(seq2);
  int32_t *matrix = calloc(len1 * len2, sizeof(int32_t));
  if (matrix == NULL) {
    return 0;
  }

  int_fast32_t diag = 0, up = 0, left = 0, score = 0, max = 0, sim = 0, i, j,
               match = 2, mismatch = -1, gap = -1;
  for (i = 1; i < len1; ++i) {
    int_fast8_t seq_char = seq1[i - 1];
    for (j = 1; j < len2; ++j) {
      sim = (seq_char == seq2[j - 1]) ? match : mismatch;
      diag = matrix[(i - 1) * len2 + (j - 1)] + sim;
      up = matrix[(i - 1) * len2 + j] + gap;
      left = matrix[i * len2 + j - 1] + gap;
      score = up;
      if (diag > up) {
        score = diag;
      }
      if (left > score) {
        score = left;
      }
      if (score > max) {
        max = score;
      }
      matrix[i * len2 + j] = score;
    }
  }

  free(matrix);
  return max;
}

int32_t main(int32_t argc, char **argv) {
  if (argc < 3) {
    printf("Usage: %s seqfile1 seqfile2\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  FILE *file1 = fopen(argv[1], "re"), *file2 = fopen(argv[2], "re");
  if (file1 == NULL || file2 == NULL) {
    printf("Couldn't open sequence file(s).\n");
    exit(EXIT_FAILURE);
  }

  size_t len1 = 0, len2 = 0;
  char *seq1 = NULL, *seq2 = NULL, read;

  while ((read = getline(&seq1, &len1, file1)) != -1) {
  }
  fclose(file1);

  while ((read = getline(&seq2, &len2, file2)) != -1) {
  }
  fclose(file2);

  printf("Max Score is %u\n", smith_waterman(seq1, seq2));
  free(seq1);
  free(seq2);
  exit(EXIT_SUCCESS);
}
