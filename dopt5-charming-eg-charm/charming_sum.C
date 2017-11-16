#include "charming_sum.h"
#include "main.decl.h"

extern /* readonly */ CProxy_Main mainProxy;
extern /* readonly */ int n_chares;
extern /* readonly */ int size;
extern /* readonly */ int *rands;

charming_sum::charming_sum() {}
charming_sum::charming_sum(CkMigrateMessage *msg) {}

void charming_sum::sum_neighbors(int i) {
  int index = thisIndex + i * n_chares;
  if (index < size) {
    printf("[%d] rand = %d\t sum with neighbors = %d\n", index, rands[index],
           rands[index] + rands[(index + 1) % size] +
               rands[(size + index - 1) % size]);
  }
  mainProxy.exit();
}

#include "charming_sum.def.h"
