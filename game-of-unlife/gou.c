#include <omp.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define DEAD 0
#define ALIVE 1
#define UNDEAD 2

void display(void *u, uint32_t w, uint32_t h) {
  uint32_t(*univ)[w] = u, x, y;
  char *codes[3] = {"  ", "\033[33mP ", "\033[36mU "}; // yellow "P", cyan "U"

  fprintf(stderr, "\033[2J"); // clear screen
  fprintf(stderr, "\033[H");  // move cursor to upper left
  for (y = 0; y < h; y++) {
    for (x = 0; x < w; x++) {
      fprintf(stderr, "%s", codes[univ[y][x]]);
    }
    fprintf(stderr, "\033[E"); // move cursor to next line
  }
  fprintf(stderr, "\033[0m"); // reset all attributes
  fflush(stderr);
  usleep(100000);
}

void evolve(void *u, int32_t w, int32_t h) {
  uint32_t(*univ)[w] = u, new[h][w];
  int32_t x, y, x1, y1, chunk, num_chunks = w * h / (STEP * STEP),
                               chunks_in_row = h / STEP,
                               chunks_in_col = w / STEP;

#pragma omp parallel for shared(u, univ, new) firstprivate(                    \
    w, h, num_chunks, chunks_in_row,                                           \
    chunks_in_col) private(x, x1, y, y1, chunk) schedule(static)
  for (chunk = 0; chunk < num_chunks; chunk++) {
    int32_t r_start = STEP * (chunk / chunks_in_col),
            c_start = STEP * (chunk % chunks_in_row),
            r_end = r_start + STEP > h ? h : r_start + STEP,
            c_end = c_start + STEP > w ? w : c_start + STEP, r, c;

    for (c = c_start; c < c_end; c += STEP) {
      for (r = r_start; r < r_end; r += STEP) {
        for (y = c_start; y < c_end; ++y) {
          for (x = r_start; x < r_end; ++x) {
            uint32_t alive = 0, undead = 0;
            for (y1 = y - 1; y1 <= y + 1; y1++) {
              for (x1 = x - 1; x1 <= x + 1; x1++) {
                if (y1 >= 0 && y1 < h && x1 >= 0 && x1 < w) {
                  alive += (univ[y1][x1] == ALIVE);
                  undead += (univ[y1][x1] == UNDEAD);
                }
              }
            }

#ifdef DEBUG
            fprintf(stderr, "univ[%u][%u] state=%u alive=%u undead=%u\n", y, x,
                    univ[y][x], alive, undead);
#endif
            if (univ[y][x] == ALIVE) {
              if (undead > 1) { // devoured
                new[y][x] = DEAD;
              } else if ((undead == 1) && (alive > 2)) { // keeps fighting
                new[y][x] = ALIVE;
              } else if ((undead == 1) && (alive <= 2)) { // zombie
                new[y][x] = UNDEAD;
              } else if (alive > 4) { // overcrowding
                new[y][x] = DEAD;
              } else {
                new[y][x] = ALIVE;
              }
            } else if (univ[y][x] == UNDEAD) {
              if (alive > 3) { // destroyed
                new[y][x] = DEAD;
              } else if ((alive == 3) && (undead == 3)) { // keeps attacking
                new[y][x] = UNDEAD;
              } else if (undead > 4) { // starvation
                new[y][x] = DEAD;
              } else {
                new[y][x] = UNDEAD;
              }
            } else {
              if (alive == 3) { // new survivor
                new[y][x] = ALIVE;
              } else if (undead > 2) { // raise undead
                new[y][x] = UNDEAD;
              } else {
                new[y][x] = DEAD;
              }
            }
          }
        }
      }
    }
  }

  for (x = 0; x < w; x++) {
    for (y = 0; y < h; y++) {
      univ[y][x] = new[y][x];
    }
  }
}

uint32_t survivors(void *u, uint32_t w, uint32_t h) {
  uint32_t(*univ)[w] = u, x, y;

  for (x = 0; x < w; x++) {
    for (y = 0; y < h; y++) {
      if (univ[y][x] == ALIVE) {
        return 1;
      }
    }
  }

  return 0;
}

void initialize(void *u, uint32_t w, uint32_t h, uint32_t seed) {
  uint32_t(*univ)[w] = u, x, y;
  srand(seed);

  for (y = 0; y < h; y++) {
    for (x = 0; x < w; x++) {
      uint32_t status = random() % 100;
      if (status < 50) {
        univ[y][x] = ALIVE;
      } else if (status < 95) {
        univ[y][x] = DEAD;
      } else {
        univ[y][x] = UNDEAD;
      }
    }
  }
}

uint32_t game(uint32_t w, uint32_t h, uint32_t max_iterations, uint32_t seed) {
  uint32_t univ[h][w], i;

  initialize(univ, w, h, seed);
  for (i = 0; i < max_iterations; i++) {
#ifdef DEBUG
    display(univ, w, h);
#endif
    if (!survivors(univ, w, h)) {
      break;
    }
#ifdef DEBUG
    fprintf(stderr, "Iteration %u\n", i);
#endif
    evolve(univ, w, h);
  }
  return i;
}

int32_t main(int32_t argc, char **argv) {
  if (argc < 2) {
    printf("Missing input filename.\n");
    exit(EXIT_FAILURE);
  }

  FILE *input = fopen(argv[1], "r");
  if (input == NULL) {
    printf("Missing file \"%s\"\n", argv[1]);
    exit(EXIT_FAILURE);
  }

  uint32_t w, h, iter, seed;
  fscanf(input, "%u %u %u %u", &iter, &w, &h, &seed);

  printf("%u\n", game(w, h, iter, seed));
}
