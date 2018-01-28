#include <cstdint>
#include <fstream>
#include <iostream>
#include <vector>

uint32_t smith_waterman(const std::string &seq1, const std::string &seq2,
                        int32_t match, int32_t mismatch, int32_t gap) {
  int32_t r = seq1.size() + 1, c = seq2.size() + 1;
  std::vector<int32_t> matrix(2 * c);
  int_fast32_t diag = 0, up = 0, _left = 0, score = 0, _max = 0, sim = 0, i, j;

  for (i = 1; i < r; i++) {
    for (j = 1; j < c; j++) {
      sim = (seq1[i - 1] == seq2[j - 1]) ? match : mismatch;
      diag = matrix[(i - 1) % 2 * c + (j - 1)] + sim;
      up = matrix[(i - 1) % 2 * c + j] + gap;
      _left = matrix[i % 2 * c + (j - 1)] + gap;
      score = up;
      if (diag > up) {
        score = diag;
      }
      if (_left > score) {
        score = _left;
      }
      if (score > _max) {
        _max = score;
      }
      matrix[i % 2 * c + j] = score;
    }
  }

  return _max;
}

int32_t main(int32_t argc, char **argv) {
  if (argc < 3) {
    std::cout << "Usage: " << argv[0] << " seqfile1 seqfile2" << std::endl;
    exit(EXIT_FAILURE);
  }

  std::ifstream f1(argv[1]), f2(argv[2]);
  std::string seq1, seq2;
  f1 >> seq1;
  f2 >> seq2;

  std::cout << "Max Score is " << smith_waterman(seq1, seq2, 2, -1, -1)
            << std::endl;
  exit(EXIT_SUCCESS);
}
