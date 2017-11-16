#include "charming_sum.decl.h"
#include "main.h"

/* readonly */ CProxy_Main mainProxy;
/* readonly */ int n_chares;
/* readonly */ int size;
/* readonly */ int *rands;

Main::Main(CkArgMsg *msg) {
  if (msg->argc < 3) {
    return;
  }

  n_chares = strtol(msg->argv[1], nullptr, 0);
  size = atoi(msg->argv[2]);
  delete msg;

  rands = (int *)malloc(size * sizeof(int));

  for (int i = 0; i < size; ++i) {
    rands[i] = rand() % 100;
  }

  mainProxy = thisProxy;
  CProxy_charming_sum array = CProxy_charming_sum::ckNew(n_chares);
  for (int i = 0; i <= size / n_chares; ++i)
    array.sum_neighbors(i);
}

Main::Main(CkMigrateMessage *msg) {}
void Main::exit() { CkExit(); }

#include "main.def.h"
