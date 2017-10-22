#include <omp.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define TASKLIMIT 25

uint64_t fib(uint32_t n) {
  if (n < 2) {
    return n;
  }

  if (n < TASKLIMIT) {
    return fib(n - 1) + fib(n - 2);
  }

  uint32_t f1, f2;
#pragma omp task shared(f1)
  f1 = fib(n - 1);
#pragma omp task shared(f2)
  f2 = fib(n - 2);
#pragma omp taskwait
  return f1 + f2;
}

int32_t main(int32_t argc, char **argv) {
  if (argc < 2) {
    printf("Usage: %s <positive number>\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  uint32_t n = strtoul(argv[1], NULL, 0);

  uint64_t result;
#pragma omp parallel
#pragma omp single
  result = fib(n);

  printf("fibonacci(%d) = %ld\n", n, result);
  exit(EXIT_SUCCESS);
}
