#pragma once

#include <geometry.hpp>

// Material

class SurfaceMaterial {
  using Color = Vector<3, unsigned char>;

  Color color;

 public:
  SurfaceMaterial(Color col) : color(col[0], col[1], col[2]) {}

  Color getColor() const noexcept { return color; }
};

// Light

template <typename FloatingType>
class Light {
  using Vec3 = Vector<3, FloatingType>;

  Vec3 pos;
  FloatingType intensity;

 public:
  FloatingType getIntensity() const noexcept { return intensity; }
  Vec3 getPos() const noexcept { return pos; }

  Light(Vec3 Pos, FloatingType Intensity) : pos(Pos[0], Pos[1], Pos[2]), intensity(Intensity) {}
};

// SceneObject

template <typename FloatingType>
class SceneObject {
  using Vec3 = Vector<3, FloatingType>;
  using Color = Vector<3, unsigned char>;

 protected:
  SurfaceMaterial material;

 public:
  SceneObject(SurfaceMaterial Material) : material(Material) {}

  Color getColor() const noexcept { return material.getColor(); }

  virtual bool intersects(const Vec3& origin, const Vec3& direction, FloatingType* distance, Vec3* norm) const = 0;
  virtual ~SceneObject() {}
};

// Sphere

template <typename FloatingType>
class Sphere : public SceneObject<FloatingType> {
  using Vec3 = Vector<3, FloatingType>;

  Vec3 center;
  FloatingType radius;

 public:
  Sphere(Vec3 Center, FloatingType Radius, SurfaceMaterial Material)
      : SceneObject<FloatingType>(Material), center(Center[0], Center[1], Center[2]), radius(Radius) {}

  // equation a * t^2 + b * t + c = 0
  bool intersects(const Vec3& origin, const Vec3& direction, FloatingType* distance, Vec3* norm) const override {
    const Vec3 radius_v = origin - center;

    const FloatingType normal_v_len = (radius_v - (direction * radius_v.dotProduct(direction))).length();
    if (normal_v_len > radius) {
      return false;
    } else {
      if (distance) {
        *distance = ::sqrt(radius_v.length() + normal_v_len) - ::sqrt(radius * radius - normal_v_len);

        if (norm) {
          Vec3 point = origin + (direction * *distance);
          *norm = (point - center).normalize();
        }
      }

      return true;
    }
  }
};
