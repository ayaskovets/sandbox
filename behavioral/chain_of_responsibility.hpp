#pragma once

#include <typeinfo>

namespace patterns {

class AbstractRequest {
 public:
  virtual void interface() = 0;
};

class ConcreteRequestA : public AbstractRequest {
  void interface() override {
    // ConcreteRequestA-specific
  }
};

class ConcreteRequestB : public AbstractRequest {
  void interface() override {
    // ConcreteRequestA-specific
  }
};

class AbstractHandler {
 private:
  AbstractHandler* next_handler;

 public:
  AbstractHandler() : next_handler(nullptr) {}

  AbstractHandler* setNext(AbstractHandler* handler) {
    return next_handler = handler;
  }

  virtual AbstractRequest* handle(AbstractRequest* request) {
    if (next_handler) {
      return next_handler->handle(request);
    } else {
      return nullptr;
    }
  }
};

class ConcreteHandlerA : public AbstractHandler {
 public:
  AbstractRequest* handle(AbstractRequest* request) override {
    if (dynamic_cast<ConcreteRequestA*>(request)) {
      printf("handling A");
      // handle ConcreteRequestA
    }

    return AbstractHandler::handle(request);
  }
};

class ConcreteHandlerB : public AbstractHandler {
 public:
  AbstractRequest* handle(AbstractRequest* request) override {
    if (dynamic_cast<ConcreteRequestB*>(request)) {
      printf("handling B");
      // handle ConcreteRequestB
    }

    return AbstractHandler::handle(request);
  }
};

}  // namespace patterns

namespace patterns_cpp {
}