#pragma once

#include <algorithm>

#include "geometry.hpp"
#include "objects.hpp"
#include "scene.hpp"

struct Frame {
  size_t width;
  size_t height;

  std::vector<Color> data;

  Frame(size_t Width, size_t Height) : width(Width), height(Height) { data.resize(Width * Height); }
};

class Camera {
  using ObjectPtr = Object*;
  using LightPtr = Light*;

  float fov_h;
  Vec3f pos;

 public:
  Camera(float Fov, const Vec3f& Pos) : fov_h(Fov), pos(Pos) {}

  Frame getFrame(size_t width, size_t height, const Scene& scene) const {
    Frame frame(width, height);

    const float width_f = static_cast<float>(width);
    const float height_f = static_cast<float>(height);

    const float fov_h_rad = (fov_h / 180.0F) * 3.14159265358979323846F;
    const float fov_v_rad = 2.0F * TracerMath::atan(TracerMath::tan((fov_h_rad / 2.0F) * (height_f / width_f)));

#pragma omp parallel for
    for (long long row = 0; row < height; ++row) {
      for (long long col = 0; col < width; ++col) {
        const float x = (2.0F * (col + 0.5F) / width_f - 1) * TracerMath::tan(fov_h_rad / 2.0F);
        const float y = -(2.0F * (row + 0.5F) / height_f - 1) * TracerMath::tan(fov_v_rad / 2.0F);
        const float z = -1.0F;

        const Vec3f direction = Vec3f(x, y, z).normalize();

        const Vec3f color_float = scene.castRay(pos, direction);

        frame.data[col + row * width] = Color(static_cast<unsigned char>(std::max(0.0F, std::min(1.0F, color_float.x)) * 255.0F),
                                              static_cast<unsigned char>(std::max(0.0F, std::min(1.0F, color_float.y)) * 255.0F),
                                              static_cast<unsigned char>(std::max(0.0F, std::min(1.0F, color_float.z)) * 255.0F));
      }
    }

    return frame;
  }
};
