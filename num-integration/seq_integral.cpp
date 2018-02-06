#include <iostream>
#include <omp.h>

template <typename Method, typename F, typename Float>
double integrate(F f, Float a, Float b, int32_t steps, Method m) {
  double s = 0, h = (b - a) / steps;
#pragma omp parallel for reduction(+ : s)
  for (int32_t i = 0; i < steps; ++i) {
    s += m(f, a + h * i, h);
  }
  return h * s;
}

class rectangular {
public:
  enum position_type { left, middle, right };
  explicit rectangular(position_type pos) : position(pos) {}
  template <typename F, typename Float>
  double operator()(F f, Float x, Float h) const {
    switch (position) {
    case left:
      return f(x);
    case middle:
      return f(x + h / 2);
    case right:
      return f(x + h);
    }
    return 0;
  }

private:
  const position_type position;
};

double quad(double x) { return x * x; }
double lin(double x) { return x + 2; }
double cubo(double x) { return x * x * x + 9 * x * x + 18 * x + 27; }

int32_t main(int32_t argc, char **argv) {
  if (argc != 2) {
    std::cout << "Usage: " << argv[0] << " <no. of rectangles>" << std::endl;
    return 1;
  }

  int32_t r = std::stoi(argv[1]);
  double n;

  n = integrate(quad, 0.0, 1.0, r * 1, rectangular(rectangular::left));
  std::cout << "x² over [0, 1] = " << n << std::endl;

  n = integrate(lin, 0.0, 10.0, r * 10, rectangular(rectangular::left));
  std::cout << "x + 2 over [0, 10] = " << n << std::endl;

  n = integrate(cubo, 3.0, 7.0, r * 100, rectangular(rectangular::left));
  std::cout << "x³ + 9x² + 18x + 27 over [3, 7] = " << n << std::endl;

  return 0;
}
