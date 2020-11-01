#pragma once

namespace patterns {

class Event {
  // Event-specific
};

class AbstractComponent;

class AbstractMediator {
 public:
  virtual void notify(AbstractComponent* originator, Event* ev) = 0;
};

class AbstractComponent {
 protected:
  AbstractMediator* mediator;

 public:
  AbstractComponent(AbstractMediator* med) : mediator(med) {}

  void setMediator(AbstractMediator* med) { mediator = med; }
  virtual void interface() = 0;
};

class ConcreteComponentA : public AbstractComponent {
 public:
  ConcreteComponentA() : AbstractComponent(nullptr) {}

  void interface() override {
    // ComponentA-specific
    mediator->notify(this, new Event);
  }
};

class ConcreteComponentB : public AbstractComponent {
 protected:
  AbstractMediator* mediator;

 public:
  ConcreteComponentB() : AbstractComponent(nullptr) {}

  void interface() override {
    // ComponentB-specific
    mediator->notify(this, new Event);
  }
};

class ConcreteMediator : public AbstractMediator {
 private:
  ConcreteComponentA component1;
  ConcreteComponentB component2;

 public:
  ConcreteMediator(ConcreteComponentA component_a, ConcreteComponentB component_b)
      : component1(component_a), component2(component_b) {
    component_a.setMediator(this);
    component_b.setMediator(this);
  }

  void notify(AbstractComponent* originator, Event* ev) override {
    // Switch on event type
  }
};

}  // namespace patterns

namespace patterns_cpp {}