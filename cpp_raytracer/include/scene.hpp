#pragma once

#include <vector>

#include "objects.hpp"

struct Scene {
  std::vector<ObjectPtr> objects;
  std::vector<LightPtr> lights;

  Scene(std::vector<ObjectPtr>&& Objects, std::vector<LightPtr>&& Lights) : objects(Objects), lights(Lights) {}

  Vec3f castRay(const Vec3f& origin, const Vec3f& direction, size_t depth = 0) const {
    Vec3f point;
    Vec3f norm_v;

    ObjectPtr intersec_object = nullptr;
    if (depth < 5 && (intersec_object = getIntersection(origin, direction, nullptr, &point, &norm_v))) {
      const Material& material = intersec_object->material;

      float diffuse_intensity = 0.0F;
      float specular_intensity = 0.0F;

      // lights
      for (const LightPtr light : lights) {
        const Vec3f light_direction = (light->pos - point).normalize();
        const float light_distance = (light->pos - point).length();

        // shadows
        Vec3f shadow_origin = dotProduct(light_direction, norm_v) < 0 ? point - norm_v * 1e-3F : point + norm_v * 1e-3F;
        float shadow_distance = 0.0F;

        if (getIntersection(shadow_origin, light_direction, &shadow_distance, nullptr, nullptr) &&
            shadow_distance < light_distance) {
          continue;
        }

        diffuse_intensity += light->intensity * std::max(0.0F, dotProduct(light_direction, norm_v));
        specular_intensity +=
            light->intensity *
            TracerMath::pow(std::max(0.0F, dotProduct(reflection(-light_direction, norm_v), direction)), material.specular_exp);
      }

      // reflections
      Vec3f reflection_direction = -reflection(direction, norm_v).normalize();
      Vec3f reflection_origin = dotProduct(reflection_direction, norm_v) < 0.0F ? point - norm_v * 1e-3F : point + norm_v * 1e-3F;

      // refractions
      Vec3f refraction_direction = refraction(direction, norm_v, material.refraction_idx).normalize();
      Vec3f refraction_origin = dotProduct(refraction_direction, norm_v) < 0.0F ? point - norm_v * 1e-3F : point + norm_v * 1e-3F;

      // resulting color
      const Vec3f diffuse_color = material.diffuse_color * diffuse_intensity;
      const Vec3f specular_color = Vec3f(specular_intensity, specular_intensity, specular_intensity);
      const Vec3f reflection_color = castRay(reflection_origin, reflection_direction, depth + 1);
      const Vec3f refraction_color = castRay(refraction_origin, refraction_direction, depth + 1);

      return diffuse_color * material.albedo[0] + specular_color * material.albedo[1] + reflection_color * material.albedo[2] +
             refraction_color * material.albedo[3];
    } else {
      return Vec3f(200, 200, 255) / 255;
    }
  }

  ~Scene() {
    for (auto& object : objects) {
      delete object;
    }

    for (auto& light : lights) {
      delete light;
    }
  }

 private:
  ObjectPtr getIntersection(const Vec3f& origin, const Vec3f& direction, float* distance, Vec3f* point, Vec3f* norm_v) const {
    ObjectPtr intersec_object = nullptr;

    float intersec_dist = std::numeric_limits<float>::max();
    Vec3f intersec_point;
    Vec3f intersec_norm_v;

    for (const ObjectPtr object : objects) {
      float dist = 0.0F;
      Vec3f point;
      Vec3f norm;

      if (object->intersects(origin, direction, &dist, &point, &norm) && dist < intersec_dist) {
        intersec_object = object;
        intersec_dist = dist;
        intersec_point = point;
        intersec_norm_v = norm;
      }
    }

    if (intersec_object) {
      if (distance) {
        *distance = intersec_dist;
      }

      if (point) {
        *point = intersec_point;
      }

      if (norm_v) {
        *norm_v = intersec_norm_v;
      }
    }

    return intersec_object;
  }
};

using Color = Vector<unsigned char, 3>;
