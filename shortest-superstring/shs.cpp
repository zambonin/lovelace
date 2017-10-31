#include <algorithm>
#include <fstream>
#include <iostream>
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

auto all_distinct_pairs(const std::set<std::string> &ss)
    -> std::set<std::pair<std::string, std::string>> {
  std::set<std::pair<std::string, std::string>> x;
  for (const std::string &s1 : ss) {
    for (const std::string &s2 : ss) {
      if (s1 != s2) {
        x.insert(make_pair(s1, s2));
      }
    }
  }
  return x;
}

auto highest_overlap_value(
    const std::set<std::pair<std::string, std::string>> &sp)
    -> std::pair<std::string, std::string> {
  std::vector<std::pair<std::string, std::string>> spp{};
  std::copy(sp.begin(), sp.end(), std::back_inserter(spp));

  std::vector<std::string::size_type> values{};
  for (unsigned int i = 0; i < spp.size(); ++i) {
    values.emplace_back(overlap_value(spp[i].first, spp[i].second));
  }

  auto result = std::max_element(values.begin(), values.end());
  return spp[std::distance(values.begin(), result)];
}

auto shortest_superstring(std::set<std::string> t) -> std::string {
  if (t.empty()) {
    return "";
  }
  while (t.size() > 1) {
    auto p = highest_overlap_value(all_distinct_pairs(t));
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

  std::cout << shortest_superstring(ss) << std::endl;
  exit(EXIT_SUCCESS);
}
