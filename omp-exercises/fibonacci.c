#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

uint64_t fib(uint32_t n) {
  if (n < 2) {
    return n;
  }

  uint32_t f1, f2, fn;
  f1 = fib(n - 1);
  f2 = fib(n - 2);
  fn = f1 + f2;
  return fn;
}

int32_t main(int32_t argc, char **argv) {
  if (argc < 2) {
    printf("Usage: %s <positive number>\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  uint32_t n = strtoul(argv[1], NULL, 0);

  printf("fibonacci(%d) = %ld\n", n, fib(n));
  exit(EXIT_SUCCESS);
}
