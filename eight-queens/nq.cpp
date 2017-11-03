#include <iostream>

bool safe_queen(uint32_t pos, uint32_t col, const uint32_t *board) {
  for (uint32_t q = 0; q < pos; ++q) {
    uint32_t c = board[q];
    if ((c == col) || (c == (col - (pos - q))) || (c == (col + (pos - q)))) {
      return false;
    }
  }
  return true;
}

uint32_t solve_nqueens(uint32_t current, uint32_t n, uint32_t *board) {
  uint32_t solutions = 0;
  if (current == n) {
    solutions = 1;
  } else {
    for (uint32_t c = 0; c < n; ++c) {
      if (safe_queen(current, c, board)) {
        board[current] = c;
        solutions += solve_nqueens(current + 1, n, board);
      }
    }
  }
  return solutions;
}

int32_t main(int32_t argc, char **argv) {
  if (argc != 2) {
    std::cout << "Usage: " << argv[0] << " board_side" << std::endl;
    exit(EXIT_FAILURE);
  }

  uint32_t n = std::stoul(argv[1]);
  uint32_t board[n] = {0};
  std::cout << "Solutions = " << solve_nqueens(0, n, board) << std::endl;
  exit(EXIT_SUCCESS);
}
