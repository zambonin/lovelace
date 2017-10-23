#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int32_t main(int32_t argc, char **argv) {
  if (argc < 4) {
    printf("Usage: %s [sequence size] [rand seed] [output file]\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  uint32_t size = strtoul(argv[1], NULL, 0), seed = strtoul(argv[2], NULL, 0);
  FILE *output = fopen(argv[3], "we");

  if (size == UINT32_MAX || seed == UINT32_MAX || output == NULL) {
    printf("Invalid parameter(s).\n");
    exit(1);
  }

  srandom(seed);
  const char charset[] = "ACGT";
  char str[++size];

  for (size_t i = 0; i < size - 1; ++i) {
    str[i] = charset[random() % (sizeof(charset) - 1)];
  }
  str[--size] = '\0';

  fprintf(output, "%s\n", str);
  fclose(output);

  exit(EXIT_SUCCESS);
}
