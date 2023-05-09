#pragma once

namespace patterns {

class Prototype {
 public:
  virtual Prototype* clone() = 0;
};

class ImplementationA : public Prototype {
 public:
  ImplementationA* clone() override {
    return new ImplementationA;
  }
};

class ImplementationB : public Prototype {
 public:
  ImplementationB* clone() override {
    return new ImplementationB;
  }
};

}  // namespace patterns

namespace patterns_cpp {

template <class Implementation>
class Prototype {
 public:
  Implementation cloneInterface() {
    return static_cast<Implementation*>(this)->cloneImplementation();
  }
};

class ImplementationA : public Prototype<ImplementationA> {
 public:
  ImplementationA cloneImplementation() {
    return ImplementationA();
  }
};

class ImplementationB : public Prototype<ImplementationB> {
 public:
  ImplementationB cloneImplementation() {
    return ImplementationB();
  }
};

}  // namespace patterns_cpp