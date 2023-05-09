#pragma once

namespace patterns {

class Interface {
 public:
  virtual void method() = 0;
};

class Adaptee {
 public:
  void adapteeMethod() {
    // Adaptee-specific
  }
};

class Adapter : public Interface {
 private:
  Adaptee& adaptee;

 public:
  Adapter(Adaptee& Adaptee) : adaptee(Adaptee) {}

  void method() override {
    adaptee.adapteeMethod();
  }
};

}  // namespace patterns

namespace patterns_cpp {}