#pragma once

namespace patterns {

class StateContext;

class AbstractState {
 protected:
  StateContext* context;

 public:
  void setContext(StateContext* ctx) { context = ctx; }
  virtual void interface() = 0;
};

class ConcreteStateA : public AbstractState {
 public:
  void interface() override {}
};

class ConcreteStateB : public AbstractState {
 public:
  void interface() override {}
};
class StateContext {
 private:
  AbstractState* state;

 public:
  StateContext(AbstractState* st) { transitionTo(state); }

  void transitionTo(AbstractState* st) {
    state = st;
    state->setContext(this);
  }

  void request() { state->interface(); }
};

}  // namespace patterns

namespace patterns_cpp {}