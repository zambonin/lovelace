#include <iostream>

int32_t solve_nqueens(uint32_t ld, uint32_t col, uint32_t rd, uint32_t mask) {
  uint32_t cnt = 0;
  if (col == mask) {
    return 1;
  }
  uint32_t poss = ~(ld | col | rd);
  while ((poss & mask) != 0u) {
    uint32_t bit = poss & -poss;
    poss -= bit;
    cnt += solve_nqueens((ld | bit) << 1, col | bit, (rd | bit) >> 1, mask);
  }
  return cnt;
}

int32_t main(int32_t argc, char **argv) {
  if (argc != 2) {
    std::cout << "Usage: " << argv[0] << " board_side" << std::endl;
    exit(EXIT_FAILURE);
  }

  uint32_t mask = (1 << std::stoul(argv[1])) - 1;
  std::cout << "Solutions = " << solve_nqueens(0, 0, 0, mask) << std::endl;
  exit(EXIT_SUCCESS);
}
