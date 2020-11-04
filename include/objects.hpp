#pragma once

#include <algorithm>

#include "geometry.hpp"

// Material

struct Material {
  Vec3f diffuse_color;
  Vec4f albedo;

  float specular_exp;
  float refraction_idx;

  Material(const Vec3f& Color, const Vec4f& Albedo, float SpecularExp, float RefractionIdx)
      : diffuse_color(Color), albedo(Albedo), specular_exp(SpecularExp), refraction_idx(RefractionIdx) {}
};

// Light

struct Light {
  Vec3f pos;
  float intensity;

  Light(const Vec3f& Pos, float Intensity) : pos(Pos), intensity(Intensity) {}
};

// Object

struct Object {
  Material material;

  Object(const Material& Material) : material(Material) {}

  virtual bool intersects(const Vec3f& origin, const Vec3f& direction, float* distance, Vec3f* point, Vec3f* norm) const = 0;
  virtual ~Object() {}
};

// Sphere

struct Sphere : public Object {
  Vec3f center;
  float radius;

  Sphere(const Vec3f& Center, float Radius, const Material& Mater) : Object(Mater), center(Center), radius(Radius) {}

  bool intersects(const Vec3f& origin, const Vec3f& direction_v, float* distance, Vec3f* point, Vec3f* norm) const override {
    const Vec3f radius_v = center - origin;

    const float ot_dist = dotProduct(radius_v, direction_v);
    const float ct_dist2 = dotProduct(radius_v, radius_v) - ot_dist * ot_dist;

    if (ct_dist2 > radius * radius) {
      return false;
    }

    const float pt_dist = TracerMath::sqrt(radius * radius - ct_dist2);
    const float op_dist = std::min(ot_dist - pt_dist, ot_dist + pt_dist);

    if (op_dist < 0) {
      return false;
    }

    if (distance) {
      *distance = op_dist;
    }
    if (point) {
      *point = origin + direction_v * op_dist;
    }
    if (norm) {
      *norm = ((origin + direction_v * op_dist) - center).normalize();
    }

    return true;
  }
};

// Plane

struct Plane : public Object {
  Vec3f plane_point;
  Vec3f norm_v;

  Plane(const Vec3f& Point, const Vec3f& Norm, const Material& Mater) : Object(Mater), plane_point(Point), norm_v(Norm) {
    norm_v.normalize();
  }
  Plane(const Vec3f& Point1, const Vec3f& Point2, const Vec3f& Point3, const Material& Material)
      : Object(Material), plane_point(Point1) {
    norm_v = crossProduct((Point2 - Point1), (Point3 - Point1)).normalize();
  }

  bool intersects(const Vec3f& origin, const Vec3f& direction_v, float* distance, Vec3f* point, Vec3f* norm) const override {
    const float denom = dotProduct(direction_v, norm_v);
    if (TracerMath::abs(denom) < 1e-2F) {
      return false;
    }

    const float param = dotProduct(plane_point - origin, norm_v) / denom;
    if (param < 0) {
      return false;
    }

    if (distance) {
      *distance = ((direction_v - origin) * param).length();
    }
    if (point) {
      *point = origin + direction_v * param;
    }
    if (norm) {
      *norm = denom < 0 ? norm_v : -norm_v;
    }

    return true;
  }
};

using ObjectPtr = Object*;
using LightPtr = Light*;
