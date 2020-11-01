#pragma once

namespace patterns {

class AbstractProductA {
 public:
  virtual void methodA() = 0;
};

class AbstractProductB {
 public:
  virtual void methodB() = 0;
};

class ConcreteProductA1 : public AbstractProductA {
 public:
  void methodA() override {
    // ConcreteProductA1-specific
  }
};

class ConcreteProductA2 : public AbstractProductA {
 public:
  void methodA() override {
    // ConcreteProductA2-specific
  }
};

class ConcreteProductB1 : public AbstractProductB {
 public:
  void methodB() override {
    // ConcreteProductB1-specific
  }
};

class ConcreteProductB2 : public AbstractProductB {
 public:
  void methodB() override {
    // ConcreteProductB2-specific
  }
};

class AbstractFactory {
 public:
  virtual AbstractProductA* createProductA() = 0;
  virtual AbstractProductB* createProductB() = 0;
};

class ConcreteFactory1 : public AbstractFactory {
 public:
  AbstractProductA* createProductA() override {
    return new ConcreteProductA1;
  }

  AbstractProductB* createProductB() override {
    return new ConcreteProductB1;
  }
};

class ConcreteFactory2 : public AbstractFactory {
 public:
  AbstractProductA* createProductA() override {
    return new ConcreteProductA2;
  }

  AbstractProductB* createProductB() override {
    return new ConcreteProductB2;
  }
};

}  // namespace patterns

namespace patterns_cpp {}