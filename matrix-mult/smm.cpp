#include <algorithm>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <omp.h>
#include <valarray>

template <class T> struct matrix {
  matrix(size_t _r, size_t _c)
      : r(_r), c(_c), data(std::valarray<T>(0, _r * _c)) {}

  T &operator()(size_t _r, size_t _c) { return data[_r * c + _c]; }

  friend std::ostream &operator<<(std::ostream &os, const matrix &m) {
    uint32_t cells = std::count_if(std::begin(m.data), std::end(m.data),
                                   [](const T &d) { return d != 0; });
    if (cells != 0) {
      os << m.r << " " << m.c << " " << cells << std::endl;
    }

    for (size_t i = 0; i < m.r; ++i) {
      for (size_t j = 0; j < m.c; ++j) {
        T elem = m.data[i * m.c + j];
        if (elem != 0) {
          os << i << " " << j << " " << elem << std::endl;
        }
      }
    }

    return os;
  }

  const size_t r, c;
  std::valarray<T> data;
};

matrix<int32_t> read_matrix(const char *path) {
  try {
    std::ifstream file(path);
    size_t r, c;
    int32_t value;

    file >> r >> c >> value;
    matrix<int32_t> m(r, c);

    while (file >> r >> c >> value) {
      m(r, c) = value;
    }

    return m;
  } catch (const std::exception &e) {
    return matrix<int32_t>(0, 0);
  }
}

int32_t main(int32_t argc, char **argv) {
  if (argc != 3) {
    std::cout << "Usage: " << argv[0] << " m_file_1 m_file_2" << std::endl;
    return 1;
  }

  matrix<int32_t> a = read_matrix(argv[1]), b = read_matrix(argv[2]);
  if (a.c != b.r) {
    std::cout << "Sizes are not compatible!" << std::endl;
    return 1;
  }

  matrix<int32_t> c(a.r, b.c);
#pragma omp parallel for shared(c) schedule(dynamic)
  for (size_t i = 0; i < a.r; ++i) {
    for (size_t k = 0; k < a.c; ++k) {
      int32_t r_elem = a(i, k);
      if (r_elem != 0) {
        for (size_t j = 0; j < b.c; ++j) {
          int32_t c_elem = b(k, j);
          if (c_elem != 0) {
            c(i, j) += r_elem * c_elem;
          }
        }
      }
    }
  }

  std::cout << c;

  return 0;
}
