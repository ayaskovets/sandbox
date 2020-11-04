#pragma once

#include <cstddef>
#include <fstream>
#include <vector>

#include <geometry.hpp>

class Window {
  using Pixel = Vector<3, unsigned char>;

  size_t width;
  size_t height;

  size_t n_pixels;

 public:
  Window(size_t Width, size_t Height) : width(Width), height(Height), n_pixels(width * height) {}

  size_t getWidth() const noexcept { return width; }
  size_t getHeight() const noexcept { return height; }

  void renderPPM(const char* path, const std::vector<Pixel>& buffer) const {
    if (buffer.size() < n_pixels) {
      return;
    }

    std::ofstream ofs(path);
    ofs << "P6\n" << width << " " << height << "\n255\n";

    for (size_t i = 0; i < n_pixels; ++i) {
      const Pixel& pixel = buffer[i];
      ofs << pixel[0]   // r
          << pixel[1]   // g
          << pixel[2];  // b
    }

    ofs.close();
  }
};
