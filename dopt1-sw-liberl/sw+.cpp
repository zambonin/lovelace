#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

int smith_waterman(const std::string &seq1, const std::string &seq2,
                   int match, int mismatch, int gap) {
  size_t r = seq1.size() + 1, c = seq2.size() + 1, i = 1, j;
  std::vector<int> matrix(r * c);
  int diag = 0, up = 0, left = 0, score = 0, max = 0, sim = 0;

  while (++i < r) {
    j = 1;
    while (++j < c) {
      sim = (seq1[i - 1] == seq2[j - 1]) ? match : mismatch;
      diag = matrix[(i - 1) * c + (j - 1)] + sim;
      up = matrix[(i - 1) * c + j] + gap;
      left = matrix[i * c + (j - 1)] + gap;
      score = std::max({left, diag, up, 0});
      max = std::max(max, score);
      matrix[i * c + j] = score;
    }
  }

  return max;
}

int main(int argc, char **argv) {
  if (argc < 3) {
    std::cout << "Usage: " << argv[0] << " seqfile1 seqfile2" << std::endl;
    return 1;
  }

  std::ifstream f1(argv[1]), f2(argv[2]);
  std::string seq1, seq2;
  f1 >> seq1;
  f2 >> seq2;

  std::cout << smith_waterman(seq1, seq2, 2, -1, -1) << std::endl;

  return 0;
}
