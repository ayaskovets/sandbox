#pragma once

namespace patterns {

class AbstractComponent {
 public:
  virtual void operate() = 0;
};

class ConcreteComponent : public AbstractComponent {
 public:
  void operate() {
    // ConcreteComponent-specific
  }
};

class Decorator : public AbstractComponent {
 protected:
  AbstractComponent* component;

 public:
  Decorator(AbstractComponent* Component) : component(Component) {}

  void operate() {
    if (component) {
      component->operate();
    }
  }
};

class ConcreteDecorator : public Decorator {
 public:
  ConcreteDecorator(AbstractComponent* Component) : Decorator(component) {}

  void operateExtended() {
    // ConcreteDecorator-specific
  }
};

}  // namespace patterns

namespace patterns_cpp {

template <class ConcreteComponent>
class AbstractComponent {
 public:
  void interface() {
    static_cast<ConcreteComponent*>(this)->implementation();
  }
};

class ConcreteComponent : public AbstractComponent<ConcreteComponent> {
 public:
  void implementation() {
    // ConcreteComponent-specific
  }
};

template <class ConcreteComponent>
class Decorator : public AbstractComponent<ConcreteComponent> {
 public:
  void extraInterface() {
    // ConcreteDecorator-specific
  }
};

}  // namespace patterns_cpp