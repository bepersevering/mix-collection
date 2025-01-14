#include <iostream>
#include <typeinfo>

// 引用类型的动态转换

class Base {
public:
  virtual ~Base() = default;
};

class Derived : public Base {
public:
  void show() { std::cout << "Derived class method" << std::endl; }
};

int main() { return 0; }
