#include "camera.hpp"
#include "geometry.hpp"
#include "scene.hpp"
#include "window.hpp"

#include <chrono>
#include <iostream>

/*
Albedo Hint:
0: Diffuse color
1: Specular lighting
2: Reflection
3: Refraction
*/

int main() {
  Window window(1600, 900);

  Material mirror(Vec3f(255, 255, 255) / 255, Vec4f(0, 10, 0.8, 0), 1425, 1);
  Material glass(Vec3f(153, 178, 204) / 255, Vec4f(0, 0.5, 0.1, 0.8), 125, 1.5);
  Material ivory(Vec3f(102, 102, 77) / 255, Vec4f(0.6, 0.3, 0.1, 0), 35, 1);
  Material red(Vec3f(77, 26, 26) / 255, Vec4f(0.9, 0.1, 0, 0), 10, 1);
  Material blue(Vec3f(50, 50, 75) / 255, Vec4f(0.7, 0, 0, 0), 10, 1.3);

  Camera camera(90, Vec3f(-7, 0, 15));
  Scene  scene(
      {
          new Sphere(Vec3f(10, 8, -20), 2, mirror),
          new Sphere(Vec3f(1, -1.5, -8), 1.5, glass),
          new Sphere(Vec3f(-1.5, -0.5, -18), 3, ivory),
          new Sphere(Vec3f(-7, 3, -18), 4, blue),
          new Plane(Vec3f(0, -15, 0), Vec3f(0, 1, 0), red),
          new Plane(Vec3f(20, 0, -60), Vec3f(-1, 0, 2), red),
          new Plane(Vec3f(-40, 0, -10), Vec3f(2, 0, 1), mirror),
          new Plane(Vec3f(0, 0, 100), Vec3f(0, 0, 1), red),
      },
      {new Light(Vec3f(20, 30, 20), 2.5)});

  std::chrono::time_point<std::chrono::system_clock> beg_time = std::chrono::system_clock::now();

  Frame frame = camera.getFrame(window.getWidth(), window.getHeight(), scene);
  window.renderPPM("out.ppm", frame);

  std::chrono::time_point<std::chrono::system_clock> end_time = std::chrono::system_clock::now();

  std::cout << "Time: " << std::chrono::duration<double>(end_time - beg_time).count() * 1000 << " ms\n";

  return 0;
}
