#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int32_t main(int32_t argc, char **argv) {
  if (argc < 6) {
    printf("Missing parameters.\nUsage: %s [#vertices] [#edges] [#max cost] "
           "[rand seed] [output file name]\n",
           argv[0]);
    return 1;
  }

  uint32_t v = strtoul(argv[1], NULL, 0), e = strtoul(argv[2], NULL, 0),
           max = strtoul(argv[3], NULL, 0), seed = strtoul(argv[4], NULL, 0);
  FILE *output = fopen(argv[5], "we");

  if (v == UINT32_MAX || e == UINT32_MAX || max == UINT32_MAX ||
      seed == UINT32_MAX || output == NULL) {
    printf("Invalid parameter(s).\n");
    return 1;
  }

  fprintf(output, "%u %u\n", v, e);
  srandom(seed);

  uint32_t source, dest, cost, i;
  for (i = 0; i < e; ++i) {
    source = random() % v;
    dest = random() % v;
    cost = random() % max;
    fprintf(output, "%u %u %u\n", source, dest, cost);
  }

  fclose(output);
  return 0;
}
