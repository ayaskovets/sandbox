#pragma once

namespace patterns {

class InternalA {
 public:
  void operate1() {
    // InternalA-specific
  }

  void operate3() {
    // InternalA-specific
  }
};

class InternalB {
 public:
  void operate2() {
    // InternalB-specific
  }

  void operate4() {
    // InternalB-specific
  }
};

class Facade {
 protected:
  InternalA internal_a;
  InternalB internal_b;

 public:
  void operate() {
    internal_a.operate1();
    internal_b.operate2();
    internal_a.operate3();
    internal_b.operate4();
  }
};

}  // namespace patterns

namespace patterns_cpp {
}