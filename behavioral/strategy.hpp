#pragma once

namespace patterns {

class AbstractStrategy {
 public:
  virtual void interface() = 0;
};

class ConcreteStrategyA : public AbstractStrategy {
 public:
  void interface() override {
    // ConcreteStrategyA-specific
  }
};

class ConcreteStrategyB : public AbstractStrategy {
 public:
  void interface() override {
    // ConcreteStrategyB-specific
  }
};

class Worker {
 private:
  AbstractStrategy* strategy;

 public:
  void setStrategy(AbstractStrategy* strat) { strategy = strat; }
  void work() { strategy->interface(); }
};

}  // namespace patterns

namespace patterns_cpp {}