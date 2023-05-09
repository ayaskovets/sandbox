#pragma once

namespace patterns {

class Product {
 private:
  bool propertyA;
  bool propertyB;

 public:
  Product(bool PropertyA, bool PropertyB) : propertyA(PropertyA), propertyB(PropertyB) {}
};

class AbstractProductBuilder {
 protected:
  bool propertyB;

 public:
  void setPropertyB(bool PropertyB) { propertyB = PropertyB; }
  bool getPropertyB() { return propertyB; }

  virtual Product buildProduct() = 0;
};

class ConcreteProductBuilderA : public AbstractProductBuilder {
 public:
  Product buildProduct() {
    return Product(true, propertyB);
  }
};

class ConcreteProductBuilderB : public AbstractProductBuilder {
 public:
  Product buildProduct() {
    return Product(false, propertyB);
  }
};

}  // namespace patterns

namespace patterns_cpp {}