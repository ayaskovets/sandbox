#pragma once

#include <cstddef>
#include <fstream>
#include <vector>

#include "camera.hpp"

class Window {
  size_t width;
  size_t height;

  size_t n_pixels;

 public:
  constexpr Window(size_t Width, size_t Height) : width(Width), height(Height), n_pixels(width * height) {}

  size_t getWidth() const noexcept { return width; }
  size_t getHeight() const noexcept { return height; }

  void renderPPM(const char* path, const Frame& frame) const {
    std::ofstream ofs(path, std::ios::binary);
    ofs << "P6\n" << width << " " << height << "\n255\n";

    for (size_t i = 0; i < n_pixels; ++i) {
      ofs << frame.data[i].x   // r
          << frame.data[i].y   // g
          << frame.data[i].z;  // b
    }

    ofs.close();
  }
};
