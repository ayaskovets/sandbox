#pragma once

namespace patterns {

class AbstractProduct {
 public:
  virtual void method() = 0;
};

class ConcreteProductA : public AbstractProduct {
 public:
  void method() override {
    // ConcreteProductA-specific
  }
};

class ConcreteProductB : public AbstractProduct {
 public:
  void method() override {
    // ConcreteProductB-specific
  }
};

class AbstractCreator {
 public:
  virtual AbstractProduct* factoryMethod() = 0;
};

class ConcreteCreatorA : public AbstractCreator {
 public:
  AbstractProduct* factoryMethod() override {
    return new ConcreteProductA;
  }
};

class ConcreteCreatorB : public AbstractCreator {
 public:
  AbstractProduct* factoryMethod() override {
    return new ConcreteProductB;
  }
};

}  // namespace patterns

namespace patterns_cpp {

template <class ConcreteProduct>
class AbstractProduct {
 public:
  void interface() {
    static_cast<ConcreteProduct*>(this)->implementation();
  }
};

class ConcreteProductA : public AbstractProduct<ConcreteProductA> {
 public:
  void implementation() {
    // ConcreteProductA-specific
  }
};

class ConcreteProductB : public AbstractProduct<ConcreteProductB> {
 public:
  void implementation() {
    // ConcreteProductB-specific
  }
};

class AbstractCreator {
 public:
  template <class ConcreteProduct>
  AbstractProduct<ConcreteProduct> factoryMethod() const {
    return ConcreteProduct();
  }
};

}  // namespace patterns_cpp