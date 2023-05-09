#pragma once

#include <list>

namespace patterns {

class AbstractSubject;

class AbstractObserver {
 public:
  virtual void update(AbstractSubject* subject) = 0;
};

class ConcreteObserver : public AbstractObserver {
 public:
  void update(AbstractSubject* subject) override {
    // ConcreteObserver-specific
  }
};

class AbstractSubject {
 public:
  virtual void attach(AbstractObserver* observer) = 0;
  virtual void detach(AbstractObserver* observer) = 0;
  virtual void notify() = 0;
};

class ConcreteSubject : public AbstractSubject {
 protected:
  std::list<AbstractObserver*> subscribers;

 public:
  void attach(AbstractObserver* observer) override { subscribers.push_back(observer); }
  void detach(AbstractObserver* observer) override { subscribers.remove(observer); }
  void notify() override {
    for (const auto observer : subscribers) {
      observer->update(this);
    }
  }
};

}  // namespace patterns

namespace patterns_cpp {}