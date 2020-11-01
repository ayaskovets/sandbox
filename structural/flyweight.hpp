#pragma once

#include <algorithm>
#include <vector>

#include <cstdio>

namespace patterns {

class Flyweight {
 private:
  int param;

 public:
  Flyweight(int Param) : param(Param) {
    printf("FLW with %d created\n", param);
  }

  int getParam() const {
    return param;
  }
};

class FlyweightFactory {
 private:
  std::vector<Flyweight*> storage;

 public:
  Flyweight* getFlyweight(int param) {
    auto cached_flyweight = std::find_if(storage.cbegin(), storage.cend(),
                                         [&param](const Flyweight* flyweight) {
                                           return flyweight->getParam() == param;
                                         });

    if (cached_flyweight != storage.cend()) {
      return *cached_flyweight;
    } else {
      storage.push_back(new Flyweight(param));
      return storage.back();
    }
  }
};

class FlyweightUser {
 private:
  Flyweight* flyweight;
  // FlyweightUser-specific members

 public:
  FlyweightUser(Flyweight* flyw) : flyweight(flyw) {}

  void interface();
  // FlyweightUser-specific methods
};

}  // namespace patterns

namespace patterns_cpp {
}