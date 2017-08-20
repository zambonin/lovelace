#include <iostream>
#include <omp.h>
#include <sys/time.h>

void _time(double *t) {
  static int sec = -1;
  struct timeval tv = {};

  gettimeofday(&tv, (struct timezone *)nullptr);

  if (sec < 0) {
    sec = tv.tv_sec;
  }
  *t = (tv.tv_sec - sec) + 1.0e-6 * tv.tv_usec;
}

template <typename Method, typename F, typename Float>
double integrate(F f, Float a, Float b, int steps, Method m) {
  double s = 0;
  double h = (b - a) / steps;
#pragma omp parallel for reduction(+ : s)
  for (int i = 0; i < steps; ++i) {
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

int main(int /*argc*/, char *argv[]) {
  double n, s, e;
  int r;

  try {
    r = std::stoi(argv[1]);
  } catch (const std::exception &e) {
    std::cout << "Usage: " << argv[0] << " <no. of rectangles>" << std::endl;
    return 1;
  }

  _time(&s);
  n = integrate(quad, 0.0, 1.0, r * 1, rectangular(rectangular::left));
  _time(&e);
  std::cout << "(" << e - s << "s) x² over [0, 1] = " << n << std::endl;

  _time(&s);
  n = integrate(lin, 0.0, 10.0, r * 10, rectangular(rectangular::left));
  _time(&e);
  std::cout << "(" << e - s << "s) x + 2 over [0, 10] = " << n << std::endl;

  _time(&s);
  n = integrate(cubo, 3.0, 7.0, r * 100, rectangular(rectangular::left));
  _time(&e);
  std::cout << "(" << e - s << "s) x³ + 9x² + 18x + 27 over [3, 7] = " << n
            << std::endl;

  return 0;
}
