#include <algorithm>
#include <iostream>
#include <set>

inline auto all_permutations(std::string s) -> std::set<std::string> {
  std::sort(s.begin(), s.end());
  std::set<std::string> x;
  do {
    x.insert(s);
  } while (std::next_permutation(s.begin(), s.end()));
  return x;
}

int32_t main(int32_t argc, char **argv) {
  if (argc != 2) {
    std::cout << "Usage: " << argv[0] << " string" << std::endl;
    exit(EXIT_FAILURE);
  }

  std::set<std::string> ss = all_permutations(argv[1]);

  std::cout << ss.size() << std::endl;
  for (const std::string &s : ss) {
    std::cout << s << std::endl;
  }

  exit(EXIT_SUCCESS);
}
