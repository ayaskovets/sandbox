#pragma once

namespace patterns {

class ConcreteObjectA;
class ConcreteObjectB;

class AbstractVisitor {
 public:
  virtual void visitConcreteObjectA(ConcreteObjectA* object) = 0;
  virtual void visitConcreteObjectB(ConcreteObjectB* object) = 0;
};

class ConcreteVisitor1 : public AbstractVisitor {
 public:
  void visitConcreteObjectA(ConcreteObjectA* object) override {
    // ConcreteVisitor1-specific
  }
  void visitConcreteObjectB(ConcreteObjectB* object) override {
    // ConcreteVisitor1-specific
  }
};

class ConcreteVisitor2 : public AbstractVisitor {
 public:
  void visitConcreteObjectA(ConcreteObjectA* object) override {
    // ConcreteVisitor2-specific
  }
  void visitConcreteObjectB(ConcreteObjectB* object) override {
    // ConcreteVisitor2-specific
  }
};

class AbstractObject {
 public:
  virtual void accept(AbstractVisitor* visitor) = 0;
};

class ConcreteObjectA : public AbstractObject {
 public:
  void accept(AbstractVisitor* visitor) override { visitor->visitConcreteObjectA(this); }
};

class ConcreteObjectB : public AbstractObject {
 public:
  void accept(AbstractVisitor* visitor) override { visitor->visitConcreteObjectB(this); }
};

}  // namespace patterns

namespace patterns_cpp {}