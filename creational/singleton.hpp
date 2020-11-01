#pragma once

namespace patterns {

class Singleton {
 private:
  static Singleton* inst;

  Singleton() = default;

 public:
  Singleton(const Singleton&) = delete;
  Singleton operator=(Singleton&) = delete;

  static Singleton* instance() noexcept {
    if (!inst) {
      inst = new Singleton;
    }

    return inst;
  }
};

Singleton* Singleton::inst = nullptr;

}  // namespace patterns

namespace patterns_cpp {

class Singleton {
 private:
  Singleton() = default;

 public:
  Singleton(const Singleton&) = delete;
  Singleton operator=(Singleton&) = delete;

  Singleton(Singleton&&) = delete;
  Singleton operator=(Singleton&&) = delete;

  static Singleton& instance() noexcept {
    static Singleton inst;
    return inst;
  }
};

}  // namespace patterns