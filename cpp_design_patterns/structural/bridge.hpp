#pragma once

namespace patterns {

class AbstractProductImplementation {
 public:
  virtual void implementation() = 0;
};

class AbstractProductInterface {
 protected:
  AbstractProductImplementation* implementation;

 public:
  AbstractProductInterface(AbstractProductImplementation* concreteImplementation) : implementation(concreteImplementation) {}

  void interface() {
    implementation->implementation();
  }
};

class ConcreteProductImplementation : public AbstractProductImplementation {
 public:
  void implementation() override {
    // ConcreteProductImplementation-specific
  }
};

class ConcreteProductInterface : public AbstractProductInterface {
 public:
  ConcreteProductInterface(AbstractProductImplementation* concreteImplementation) : AbstractProductInterface(concreteImplementation) {}

  void extendedInterface() {
    // ConcreteProductInterface-specific
  }
};

}  // namespace patterns

namespace patterns_cpp {

template <class AbstractProductImplementation>
class AbstractProductInterface {
 public:
  void interface() {
    static_cast<AbstractProductImplementation*>(this)->implementation();
  }
};

template <class ConcreteProductImplementation>
class ConcreteProductInterface : public AbstractProductInterface<ConcreteProductImplementation> {
 public:
  void extendedInterface() {
    // ConcreteProductInterface-specific
  }
};

class ConcreteProductImplementation {
 public:
  void implementation() {
    // ConcreteProductImplementation-specific
  }
};

}  // namespace patterns_cpp