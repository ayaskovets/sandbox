#pragma once

#include <list>

namespace patterns {

class Component {
 public:
  virtual void operate() = 0;

  virtual void add(Component* component) {
    throw "Not implemented";
  }

  virtual void remove(Component* component) {
    throw "Not implemented";
  }
};

class Leaf : public Component {
 public:
  void operate() override {
    // Leaf-specific
  }
};

class Node : public Component {
 private:
  std::list<Component*> children;

 public:
  void operate() {
    // Node-specific
  }

  void add(Component* component) override {
    children.push_back(component);
  }

  void remove(Component* component) override {
    children.remove(component);
  }
};

}  // namespace patterns

namespace patterns_cpp {
}