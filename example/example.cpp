#include "camera.hpp"
#include "scene.hpp"
#include "window.hpp"

using FloatingType = float;
using Vec3 = Vector<3, FloatingType>;
using Pixel = Vector<3, unsigned char>;
using Color = Pixel;

int main() {
  Window window(1024, 768);

  SurfaceMaterial wood(Color(139, 90, 43));
  SurfaceMaterial metal(Color(123, 144, 149));

  Camera<FloatingType, Pixel> camera(90, Vec3(0, 0, 0));
  Scene<FloatingType> scene(
      {
          new Sphere<FloatingType>(Vec3(-5, 2, -18), 1.5, wood),
          new Sphere<FloatingType>(Vec3(-3, -2, -10), 2, metal),
          new Sphere<FloatingType>(Vec3(4, 4, -20), 4, wood),
      },
      {
          new Light<FloatingType>(Vec3(-20, 20, 20), 1.8),
      });

  std::vector<Pixel> frame = camera.getFrame(window, scene);
  window.renderPPM("out.ppm", frame);

  return 0;
}
