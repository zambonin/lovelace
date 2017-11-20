#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <cmath>
#include <iostream>

template <typename T> class vector3 {
public:
  vector3() : x(T(0)), y(T(0)), z(T(0)) {}

  explicit vector3(T v) : x(v), y(v), z(v) {}

  vector3(T xx, T yy, T zz, bool normalized = false) : x(xx), y(yy), z(zz) {
    if (normalized) {
      T n = norm();
      if (n > 0) {
        T factor = 1 / sqrt(n);
        x *= factor, y *= factor, z *= factor;
      }
    }
  }

  ~vector3() = default;

  vector3(const vector3<T> &v, bool normalized = false)
      : vector3(v.x, v.y, v.z, normalized) {}

  vector3(vector3 &&v) noexcept = default;

  vector3<T> &operator=(const vector3<T> &v) = default;

  vector3 &operator=(vector3 &&v) noexcept = default;

  vector3<T> operator-() const { return vector3<T>(-x, -y, -z); }

  vector3<T> operator+(const vector3<T> &v) const {
    return vector3<T>(x + v.x, y + v.y, z + v.z);
  }

  vector3<T> operator-(const vector3<T> &v) const {
    return vector3<T>(x - v.x, y - v.y, z - v.z);
  }

  vector3<T> operator*(const T &s) const {
    return vector3<T>(x * s, y * s, z * s);
  }

  vector3<T> operator*(const vector3<T> &v) const {
    return vector3<T>(x * v.x, y * v.y, z * v.z);
  }

  vector3<T> &operator+=(const vector3<T> &v) {
    x += v.x, y += v.y, z += v.z;
    return *this;
  }

  vector3<T> &operator-=(const vector3<T> &v) {
    x -= v.x, y -= v.y, z -= v.z;
    return *this;
  }

  vector3<T> &operator*=(const vector3<T> &v) {
    x *= v.x, y *= v.y, z *= v.z;
    return *this;
  }

  T norm() const { return x * x + y * y + z * z; }

  T length() const { return sqrt(norm()); }

  T dot(const vector3<T> &v) const { return x * v.x + y * v.y + z * v.z; }

  T x, y, z;
};

class sphere {
public:
  sphere(const vector3<float> &c, const float &r, const vector3<float> &sc,
         const float &refl = 0, const float &transp = 0,
         const vector3<float> &ec = vector3<float>(0))
      : center(c), radius(r), radius_sq(r * r), sf_color(sc), em_color(ec),
        transparency(transp), reflection(refl) {}

  bool intersect(const vector3<float> &rayorig, const vector3<float> &raydir,
                 float *t) const {
    vector3<float> l = center - rayorig;
    float tca = l.dot(raydir), d2 = l.dot(l) - tca * tca,
          thc = sqrt(radius_sq - d2), t0 = tca - thc, t1 = tca + thc;

    bool valid = !((tca < 0) || (d2 > radius_sq) || (t0 < 0 && t1 < 0));
    if (valid) {
      *t = (t0 < 0 || t1 < 0) ? std::max(t0, t1) : std::min(t0, t1);
    }

    return valid;
  }

  vector3<float> center;
  float radius, radius_sq;
  vector3<float> sf_color, em_color;
  float transparency, reflection;
};

#endif // STRUCTURES_H
