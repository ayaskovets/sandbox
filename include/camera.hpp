#pragma once

#include "geometry.hpp"
#include "objects.hpp"
#include "scene.hpp"
#include "window.hpp"

template <typename FloatingType, typename Pixel>
class Camera {
  const FloatingType RAD_DEGREES = 180.0 / 3.14159265358979323846;

  using Vec3 = Vector<3, FloatingType>;
  using ObjectPtr = SceneObject<FloatingType>*;
  using LightPtr = Light<FloatingType>*;

  FloatingType fov_h;
  Vec3 pos;

 public:
  explicit Camera(FloatingType Fov, Vec3 Pos) : fov_h(Fov), pos(Pos[0], Pos[1], Pos[2]) {}

  std::vector<Pixel> getFrame(const Window& window, const Scene<FloatingType>& scene) const {
    std::vector<Pixel> frame(window.getWidth() * window.getHeight());

    const FloatingType width = static_cast<FloatingType>(window.getWidth());
    const FloatingType height = static_cast<FloatingType>(window.getHeight());

    const FloatingType fov_h_r = fov_h / RAD_DEGREES;
    const FloatingType fov_v_r = 2 * atan(tan(fov_h_r / 2 * height / width));

    for (size_t row = 0; row < height; ++row) {
      for (size_t col = 0; col < width; ++col) {
        const FloatingType x = (2 * (col + static_cast<FloatingType>(0.5)) / width - 1) * tan(fov_h_r / 2);
        const FloatingType y = -(2 * (row + static_cast<FloatingType>(0.5)) / height - 1) * tan(fov_v_r / 2);

        Vec3 direction = Vec3(x, y, -1).normalize();

        ObjectPtr closest_object = nullptr;
        Vec3 closest_object_norm;
        FloatingType closest_distance = std::numeric_limits<FloatingType>::max();

        for (const ObjectPtr object : scene.objects) {
          FloatingType distance = 0;
          if (object->intersects(pos, direction, &distance, &closest_object_norm) && distance > 0 &&
              distance < closest_distance) {
            closest_object = object;
            closest_distance = distance;
          }
        }

        if (closest_object) {
          Vec3 point = pos + (direction * closest_distance);

          FloatingType lights_intensity = 0;
          for (const LightPtr light : scene.lights) {
            Vec3 light_direction = (light->getPos() - point).normalize();
            lights_intensity += light->getIntensity() * std::max(0.0F, light_direction.dotProduct(closest_object_norm));
          }

          frame[col + row * width] = closest_object->getColor() * lights_intensity;
        } else {
          frame[col + row * width] = Pixel(200, 200, 255);
        }
      }
    }

    return frame;
  }
};
