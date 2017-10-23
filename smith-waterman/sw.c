#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int smith_waterman(const char *seq1, const char *seq2) {
  int len1 = strlen(seq1), len2 = strlen(seq2);
  int *matrix = calloc(len1 * len2, sizeof(int));
  if (matrix == NULL) {
    return -1;
  }

  int diag = 0, up = 0, left = 0, score = 0, max = 0, s = 0;
  for (int i = 1; i < len1; ++i) {
    for (int j = 1; j < len2; ++j) {
      s = (seq1[i - 1] == seq2[j - 1]) ? 2 : -1;
      diag = matrix[(i - 1) * len2 + (j - 1)] + s;
      up = matrix[(i - 1) * len2 + j] - 1;
      left = matrix[i * len2 + j - 1] - 1;
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

int main(int argc, char **argv) {
  if (argc < 3) {
    printf("Usage: %s seqfile1 seqfile2\n", argv[0]);
    return 1;
  }

  FILE *file1 = fopen(argv[1], "re"), *file2 = fopen(argv[2], "re");
  if (file1 == NULL || file2 == NULL) {
    printf("Couldn't open sequence file(s).\n");
    return 1;
  }

  size_t len1 = 0, len2 = 0;
  char *seq1 = NULL, *seq2 = NULL, read;

  while ((read = getline(&seq1, &len1, file1)) != -1) {
  }
  while ((read = getline(&seq2, &len2, file2)) != -1) {
  }

  printf("Max Score is %d\n", smith_waterman(seq1, seq2));

  free(seq1);
  free(seq2);
  fclose(file1);
  fclose(file2);

  return 0;
}
