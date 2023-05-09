#pragma once

namespace patterns {

class WorkerInterface {
 public:
  virtual void operate() = 0;
};

class Worker : public WorkerInterface {
 public:
  void operate() {
    // ConcreteWorker-specific
  }
};

class Proxy : public WorkerInterface {
 protected:
  Worker worker;

 public:
  Proxy(Worker worker) : worker(worker) {}

  void operate() {
    // Proxy-specific
    worker.operate();
  }

  // other Proxy-specific methods
};

}  // namespace patterns

namespace patterns_cpp {
}