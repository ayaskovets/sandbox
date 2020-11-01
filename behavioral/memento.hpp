#pragma once

#include <list>

namespace patterns {

class State {
  // State implementation
};

class Memento {
 private:
  State* state;

 public:
  Memento(State* st) : state(st) {}

  State* getState() { return state; }
};

class Originator {
 private:
  State* state;

 public:
  Memento* createMemento() { return new Memento(state); }

  void restore(Memento* memento) { state = memento->getState(); }
};

class Caretaker {
 private:
  std::list<Memento*> mementos;
  Originator* originator;

 public:
  Caretaker(Originator* orig) : originator(orig) {}

  void backup() { mementos.push_back(originator->createMemento()); }
  // Caretaker-specific
};

}  // namespace patterns

namespace patterns_cpp {}