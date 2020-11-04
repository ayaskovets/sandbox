#pragma once

#include <vector>

#include <objects.hpp>

template <typename FloatingType>
class Scene {
  using ObjectPtr = SceneObject<FloatingType>*;
  using LightPtr = Light<FloatingType>*;

 public:
  std::vector<ObjectPtr> objects;
  std::vector<LightPtr> lights;

  Scene() {}
  Scene(std::vector<ObjectPtr>&& Objects, std::vector<LightPtr>&& Lights) : objects(Objects), lights(Lights) {}

  ~Scene() {
    for (auto& object : objects) {
      delete object;
    }
  }
};
