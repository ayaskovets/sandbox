#pragma once

#include <cstddef>
#include <fstream>
#include <vector>

#include "camera.hpp"

class Window {
  size_t width;
  size_t height;

 public:
  constexpr Window(size_t Width, size_t Height) : width(Width), height(Height) {}

  size_t getWidth() const noexcept { return width; }
  size_t getHeight() const noexcept { return height; }

  void renderPPM(const char* path, const Frame& frame) const {
    std::ofstream ofs(path, std::ios::binary);
    ofs << "P6\n"
        << width << " " << height << "\n255\n";

    for (const Color& color : frame.data) {
      ofs << color.x   // r
          << color.y   // g
          << color.z;  // b
    }

    ofs.close();
  }
};
