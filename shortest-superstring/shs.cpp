#include <fstream>
#include <iostream>
#include <set>

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

auto all_suffixes(const std::string &x) -> std::set<std::string> {
  std::set<std::string> ss;
  std::string::size_type n = x.size();
  while (--n != 0u) {
    ss.insert(x.substr(n));
  }
  return ss;
}

auto common_suffix_and_prefix(const std::string &a, const std::string &b)
    -> std::string {
  if (a.empty() || b.empty()) {
    return "";
  }
  std::string x;
  for (const std::string &s : all_suffixes(a)) {
    if (is_prefix(s, b) && s.size() > x.size()) {
      x = s;
    }
  }
  return x;
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
  std::pair<std::string, std::string> x = *(sp.begin());
  for (const std::pair<std::string, std::string> &p : sp) {
    if (overlap_value(p.first, p.second) > overlap_value(x.first, x.second)) {
      x = p;
    }
  }
  return x;
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
