#include <algorithm>
#include <fstream>
#include <iostream>
#include <omp.h>
#include <set>
#include <vector>

auto is_prefix(const std::string &a, const std::string &b) -> bool {
  if (a.size() > b.size()) {
    return false;
  }
  if (!(std::mismatch(a.begin(), a.end(), b.begin()).first == a.end())) {
    return false;
  }
  return true;
}

inline auto remove_prefix(const std::string &x, std::string::size_type n)
    -> std::string {
  if (x.size() > n) {
    return x.substr(n);
  }
  return x;
}

auto common_suffix_and_prefix(const std::string &a, const std::string &b)
    -> std::string {
  if (a.empty() || b.empty()) {
    return "";
  }
  std::string x;
  std::string::size_type n = a.size();
  while (--n != 0u) {
    x = a.substr(n);
    if (is_prefix(x, b)) {
      return x;
    }
  }
  return "";
}

inline auto overlap_value(const std::string &s, const std::string &t)
    -> std::string::size_type {
  return common_suffix_and_prefix(s, t).size();
}

auto overlap(const std::string &s, const std::string &t) -> std::string {
  std::string c = common_suffix_and_prefix(s, t);
  return s + remove_prefix(t, c.size());
}

auto pair_of_strings_with_highest_overlap_value(const std::set<std::string> &sp)
    -> std::pair<std::string, std::string> {
  std::vector<std::string> spp{};
  std::copy(sp.begin(), sp.end(), std::back_inserter(spp));
  std::vector<std::pair<std::string, std::string>> pairs{};
  std::vector<std::string::size_type> values{};

#pragma omp declare reduction (merge_pairs \
    : std::vector<std::pair<std::string, std::string>> \
    : omp_out.insert(omp_out.end(), omp_in.begin(), omp_in.end()))
#pragma omp declare reduction (merge_values \
    : std::vector<std::string::size_type> \
    : omp_out.insert(omp_out.end(), omp_in.begin(), omp_in.end()))
#pragma omp parallel for reduction(merge_pairs : pairs) \
  reduction(merge_values : values) schedule(dynamic)
  for (size_t i = 0; i < spp.size(); ++i) {
    for (size_t j = i + 1; j < spp.size(); ++j) {
      auto w1 = spp[i], w2 = spp[j];
      auto _overlap = overlap_value(w1, w2);
      auto inverse = overlap_value(w2, w1);
      if (inverse > _overlap) {
        pairs.push_back(make_pair(w2, w1));
        values.push_back(inverse);
      } else {
        pairs.push_back(make_pair(w1, w2));
        values.push_back(_overlap);
      }
    }
  }

  auto result = std::max_element(values.begin(), values.end());
  return pairs[std::distance(values.begin(), result)];
}

auto shortest_superstring(std::set<std::string> t) -> std::string {
  if (t.empty()) {
    return "";
  }
  while (t.size() > 1) {
    auto p = pair_of_strings_with_highest_overlap_value(t);
    t.erase(p.first);
    t.erase(p.second);
    t.insert(overlap(p.first, p.second));
  }
  return *(t.begin());
}

auto main(int32_t argc, char **argv) -> int32_t {
  if (argc != 2) {
    std::cout << "Usage: " << argv[0] << " input_file" << std::endl;
    exit(EXIT_FAILURE);
  }

  std::ifstream file(argv[1]);
  std::set<std::string> ss;
  std::string word;
  size_t size;

  file >> size;
  while (file >> word) {
    ss.insert(word);
  }
  file.close();

  std::cout << shortest_superstring(ss) << std::endl;
  exit(EXIT_SUCCESS);
}
