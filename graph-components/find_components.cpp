#include <algorithm>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <limits>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>

struct edge {
  friend std::istream &operator>>(std::istream &is, edge &e) {
    return is >> e.source >> e.dest >> e.cost;
  }

  uint32_t source, dest, cost;
};

struct graph {
  using arrow = std::unordered_map<uint32_t, uint32_t>;
  using matrix = std::vector<arrow>;

  explicit graph(uint32_t size) : costs(matrix(size)) {}

  std::size_t size() const { return costs.size(); }

  const arrow &operator[](uint32_t v) const { return costs[v]; }

  void operator<<(const edge &e) {
    if (costs[e.source].count(e.dest) == 0) {
      costs[e.source][e.dest] = e.cost;
    } else if (e.cost < costs[e.source][e.dest]) {
      costs[e.source][e.dest] = e.cost;
    }
    if (costs[e.dest].count(e.source) == 0) {
      costs[e.dest][e.source] = e.cost;
    } else if (e.cost < costs[e.dest][e.source]) {
      costs[e.dest][e.source] = e.cost;
    }
  }

  friend std::ostream &operator<<(std::ostream &os, const graph &g) {
    for (std::size_t i = 0; i < g.size(); ++i) {
      for (auto &e : g[i]) {
        os << i << " " << e.first << " " << e.second << std::endl;
      }
    }
    return os;
  }

  std::vector<uint32_t> components() {
    std::vector<uint32_t> cc(size(), std::numeric_limits<uint32_t>::max());
    uint32_t component = 0;

    for (std::size_t v = 0; v < cc.size(); ++v) {
      if (cc[v] == std::numeric_limits<uint32_t>::max()) {
        std::stack<uint32_t> comp;
        comp.push(v);
        while (!comp.empty()) {
          auto &cur = comp.top();
          comp.pop();
          cc[cur] = component;
          for (auto &n : (*this)[cur]) {
            if (cc[n.first] == std::numeric_limits<uint32_t>::max()) {
              comp.push(n.first);
            }
          }
        }
        ++component;
      }
    }

    return cc;
  }

  matrix costs;
};

int32_t main(int32_t argc, char **argv) {
  if (argc < 2) {
    std::cout << "Usage: " << argv[0] << " graph_file" << std::endl;
    return 1;
  }

  std::ifstream f(argv[1]);
  uint32_t v, ne;

  f >> v >> ne;
  graph g(v);
  edge e{};

  while (f >> e) {
    g << e;
  }

  for (auto &c : g.components()) {
    std::cout << c << " ";
  }
  std::cout << std::endl;

  return 0;
}
