#pragma once

#include <algorithm>
#include <cassert>
#include <cmath>
#include <initializer_list>

// Math

namespace TracerMath {

template <typename T>
T abs(T x) {
  if constexpr (std::is_same<T, float>::value) {
    return std::fabsf(x);

  } else if constexpr (std::is_same<T, long double>::value) {
    return std::fabsl(x);
  } else {
    return std::fabs(x);
  }
}

template <typename T>
T pow(T x, T exp) {
  if constexpr (std::is_same<T, float>::value) {
    return std::powf(x, exp);
  } else if constexpr (std::is_same<T, long double>::value) {
    return std::powl(x, exp);
  } else {
    return std::pow(x, exp);
  }
}

template <typename T>
T sqrt(T x) {
  if constexpr (std::is_same<T, float>::value) {
    return std::sqrtf(x);
  } else if constexpr (std::is_same<T, long double>::value) {
    return std::sqrtl(x);
  } else {
    return std::sqrt(x);
  }
}

template <typename T>
T tan(T x) {
  if constexpr (std::is_same<T, float>::value) {
    return std::tanf(x);
  } else if constexpr (std::is_same<T, long double>::value) {
    return std::tanl(x);
  } else {
    return std::tan(x);
  }
}

template <typename T>
T atan(T x) {
  if constexpr (std::is_same<T, float>::value) {
    return std::atanf(x);
  } else if constexpr (std::is_same<T, long double>::value) {
    return std::atanl(x);
  } else {
    return std::atan(x);
  }
}
}  // namespace TracerMath

// Vector

template <typename T, size_t S>
struct Vector {
  T data[S];

  Vector(std::initializer_list<T> Data) { std::copy(Data.begin(), Data.end(), data); }
  Vector() { std::fill(data, data + S, T()); }

  T& operator[](const size_t i) {
    assert(i < S);
    return data[i];
  }
  const T& operator[](const size_t i) const {
    assert(i < S);
    return data[i];
  }

  float length() const {
    float norm_squared = 0.0F;
    for (size_t i = S; i--; norm_squared += data[i] * data[i])
      ;
    return TracerMath::sqrt(norm_squared);
  }

  const Vector& normalize() {
    const float norm = length();
    for (size_t i = S; i--; data[i] /= norm)
      ;
    return *this;
  }
};

template <typename T>
struct Vector<T, 4> {
  T x, y, z, w;

  Vector(T X, T Y, T Z, T W) : x(X), y(Y), z(Z), w(W) {}
  Vector() : x(T()), y(T()), z(T()), w(T()) {}

  T& operator[](const size_t i) {
    assert(i < 4);
    return i == 3 ? w : i == 2 ? z : i == 1 ? y : x;
  }
  const T& operator[](const size_t i) const {
    assert(i < 4);
    return i == 3 ? w : i == 2 ? z : i == 1 ? y : x;
  }

  float length() const { return TracerMath::sqrt(x * x + y * y + z * z + w * w); }

  const Vector& normalize() {
    const float norm = length();
    x /= norm;
    y /= norm;
    z /= norm;
    w /= norm;
    return *this;
  }
};

template <typename T>
struct Vector<T, 3> {
  T x, y, z;

  Vector(T X, T Y, T Z) : x(X), y(Y), z(Z) {}
  Vector() : x(T()), y(T()), z(T()) {}

  T& operator[](const size_t i) {
    assert(i < 3);
    return i == 2 ? z : i == 1 ? y : x;
  }
  const T& operator[](const size_t i) const {
    assert(i < 3);
    return i == 2 ? z : i == 1 ? y : x;
  }

  float length() const { return TracerMath::sqrt(x * x + y * y + z * z); }

  const Vector& normalize() {
    const float norm = length();
    x /= norm;
    y /= norm;
    z /= norm;
    return *this;
  }
};

template <typename T>
struct Vector<T, 2> {
  T x, y;

  Vector(T X, T Y) : x(X), y(Y) {}
  Vector() : x(T()), y(T()) {}

  T& operator[](const size_t i) {
    assert(i < 2);
    return i == 1 ? y : x;
  }
  const T& operator[](const size_t i) const {
    assert(i < 2);
    return i == 1 ? y : x;
  }

  float length() const { return TracerMath::sqrt(x * x + y * y); }

  const Vector& normalize() {
    const float norm = length();
    x /= norm;
    y /= norm;
    return *this;
  }
};

template <typename T, size_t S>
Vector<T, S> operator+(const Vector<T, S>& a, const Vector<T, S>& b) {
  Vector<T, S> result;
  for (size_t i = S; i--; result[i] = a[i] + b[i])
    ;
  return result;
}

template <typename T, size_t S>
Vector<T, S> operator-(const Vector<T, S>& a, const Vector<T, S>& b) {
  Vector<T, S> result;
  for (size_t i = S; i--; result[i] = a[i] - b[i])
    ;
  return result;
}

template <typename T, size_t S>
Vector<T, S> operator*(const Vector<T, S>& a, float b) {
  Vector<T, S> result;
  for (size_t i = S; i--; result[i] = a[i] * b)
    ;
  return result;
}

template <typename T, size_t S>
Vector<T, S> operator/(const Vector<T, S>& a, float b) {
  Vector<T, S> result;
  for (size_t i = S; i--; result[i] = a[i] / b)
    ;
  return result;
}

template <typename T, size_t S>
Vector<T, S> operator-(const Vector<T, S>& a) {
  Vector<T, S> result;
  for (size_t i = S; i--; result[i] = -a[i])
    ;
  return result;
}

template <typename T, size_t S>
float dotProduct(const Vector<T, S>& a, const Vector<T, S>& b) {
  float result = 0.0F;
  for (size_t i = S; i--; result += a[i] * b[i])
    ;
  return result;
}

template <typename T>
Vector<T, 3> crossProduct(const Vector<T, 3>& a, const Vector<T, 3>& b) {
  return Vector<T, 3>(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
}

template <typename T>
Vector<T, 3> reflection(const Vector<T, 3>& vect, const Vector<T, 3>& norm) {
  return norm * 2.0F * dotProduct(vect, norm) - vect;
}

template <typename T>
Vector<T, 3> refraction(const Vector<T, 3>& vect, const Vector<T, 3>& norm, float n_t, float n_i = 1.0F) {
  const float cosi = -std::max(-1.0F, std::min(1.0F, dotProduct(vect, norm)));
  if (cosi < 0) {
    return refraction(vect, -norm, n_i, n_t);
  }

  const float n = n_i / n_t;
  const float k = 1 - n * n * (1 - cosi * cosi);

  return k < 0 ? Vector<T, 3>(1, 0, 0) : vect * n + norm * (n * cosi - TracerMath::sqrt(k));
}

using Vec4f = Vector<float, 4>;
using Vec3f = Vector<float, 3>;
using Vec2f = Vector<float, 2>;
