#pragma once

namespace patterns {

class Receiver {
 public:
  void receive() {
    // Receiver-specific
  }
};

class AbstractCommand {
 public:
  virtual void execute() = 0;
};

class ConcreteCommandA : public AbstractCommand {
 public:
  void execute() override {
    // ConcreteCommandA-specific
  }
};

class ConcreteCommandB : public AbstractCommand {
 private:
  Receiver* receiver;

 public:
  ConcreteCommandB(Receiver* cmd_receiver) : receiver(cmd_receiver) {
    // ConcreteCommandB-specific
  }

  void execute() override {
    receiver->receive();
    // ConcreteCommandB-specific
  }
};

class Invoker {
 private:
  AbstractCommand* command;

 public:
  Invoker() : command(nullptr) {}

  void setCommand(AbstractCommand* cmd) {
    command = cmd;
  }

  void invoke() {
    command->execute();
    // Invoker-specific
  }
};

}  // namespace patterns

namespace patterns_cpp {
}