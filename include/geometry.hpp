#pragma once

#include <algorithm>
#include <cassert>
#include <cmath>
#include <type_traits>

// Vector
template <typename FloatingType>
FloatingType sqrt(FloatingType x) {
  if constexpr (std::is_same<FloatingType, float>::value) {
    return std::sqrtf(x);
  } else if constexpr (std::is_same<FloatingType, long double>::value) {
    return std::sqrtl(x);
  } else {
    return std::sqrt(x);
  }
}

template <typename FloatingType>
FloatingType tan(FloatingType x) {
  if constexpr (std::is_same<FloatingType, float>::value) {
    return std::tanf(x);
  } else if constexpr (std::is_same<FloatingType, long double>::value) {
    return std::tanl(x);
  } else {
    return std::tan(x);
  }
}

template <typename FloatingType>
FloatingType atan(FloatingType x) {
  if constexpr (std::is_same<FloatingType, float>::value) {
    return std::atanf(x);
  } else if constexpr (std::is_same<FloatingType, long double>::value) {
    return std::atanl(x);
  } else {
    return std::atan(x);
  }
}

template <size_t Dim, typename FloatingType>
class Vector {
  FloatingType data[Dim];

 public:
  template <typename... Args>
  explicit Vector(Args&&... values) : data{static_cast<FloatingType>(std::forward<Args>(values))...} {}
  Vector() {
    for (size_t i = 0; i < Dim; ++i) {
      data[i] = static_cast<FloatingType>(0);
    }
  }

  constexpr size_t size() const { return Dim; }

  FloatingType& operator[](size_t i) {
    assert(i < Dim);
    return data[i];
  }

  const FloatingType& operator[](size_t i) const {
    assert(i < Dim);
    return data[i];
  }

  FloatingType length() const {
    FloatingType norm_squared = 0;
    for (size_t i = 0; i < Dim; ++i) {
      norm_squared += data[i] * data[i];
    }
    return ::sqrt(norm_squared);
  }

  const Vector& normalize() {
    const FloatingType norm = length();
    for (size_t i = 0; i < Dim; ++i) {
      data[i] /= norm;
    }
    return *this;
  }

  template <typename MultiplierType>
  Vector operator*(MultiplierType mul) const {
    Vector multiplied;
    for (size_t i = 0; i < Dim; ++i) {
      multiplied[i] = data[i] * mul;
    }
    return multiplied;
  }

  template <typename DivisorType>
  Vector operator/(DivisorType div) const {
    Vector divided;
    for (size_t i = 0; i < Dim; ++i) {
      divided[i] = data[i] / div;
    }
    return divided;
  }

  Vector operator+(const Vector& add) const {
    Vector res;
    for (size_t i = 0; i < Dim; ++i) {
      res[i] = data[i] + add[i];
    }
    return res;
  }

  Vector operator-(const Vector& sub) const {
    Vector res;
    for (size_t i = 0; i < Dim; ++i) {
      res[i] = data[i] - sub[i];
    }
    return res;
  }

  FloatingType dotProduct(const Vector& mul) const {
    FloatingType dot_product = FloatingType();
    for (size_t i = 0; i < Dim; ++i) {
      dot_product += data[i] * mul[i];
    };
    return dot_product;
  }
};
