#include <omp.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define SEED 26

static inline void _add(uint32_t *a, const uint32_t *b) { *a += *b; }
static inline void _sub(uint32_t *a, const uint32_t *b) { *a -= *b; }
static inline void _mul(uint32_t *a, const uint32_t *b) { *a *= *b; }
static inline void _xor(uint32_t *a, const uint32_t *b) { *a ^= *b; }

typedef void (*func_ptr)(uint32_t *, const uint32_t *);
func_ptr setup(char operator, uint32_t **vector, uint32_t **buffer,
               uint32_t *partial, uint32_t *offset) {
  switch (operator) {
  case '+':
    (*buffer)[0] = 0;
    return &_add;
  case '-':
    (*buffer)[0] = (*vector)[0] << 1u;
    return &_sub;
  case '*':
    (*buffer)[0] = *partial = *offset = 1;
    return &_mul;
  case '^':
    (*buffer)[0] = 0;
    return &_xor;
  default:
    return &_add;
  }
}

void scan(uint32_t *vec, uint32_t *result, uint64_t size, char operator) {
  uint32_t *buffer;
  func_ptr func;

#pragma omp parallel
  {
    uint32_t part = 0, offset = 0, tid = omp_get_thread_num() + 1;
    uint64_t i;
#pragma omp single
    buffer = malloc((omp_get_num_threads() + 1) * sizeof(uint32_t));
    func = setup(operator, &vec, &buffer, &part, &offset);

#pragma omp for
    for (i = 0; i < size; ++i) {
      func(&part, &vec[i]);
      result[i] = part;
    }
    buffer[tid] = part;

#pragma omp barrier
    for (i = 0; i < tid; ++i) {
      func(&offset, &buffer[i]);
    }
#pragma omp for
    for (i = 0; i < size; ++i) {
      func(&result[i], &offset);
    }
  }
  free(buffer);
}

int32_t main(int32_t argc, char **argv) {
  if (argc < 3) {
    printf("Usage: %s <positive number> [+-*^]\n", argv[0]);
    return 1;
  }

  uint64_t i = 0, n = strtoul(argv[1], NULL, 0);
  uint32_t *vec = (uint32_t *)calloc(n, sizeof(uint32_t)),
           *res = (uint32_t *)malloc(n * sizeof(uint32_t));

  srandom(SEED);
  for (i = 0; i < n; i++) {
    vec[i] = (random() % 5) + 1;
  }

  scan(vec, res, n, argv[2][0]);

  for (i = 0; i < n; ++i) {
    printf("%d ", res[i]);
  }
  printf("\n");

  free(vec);
  free(res);

  return 0;
}
