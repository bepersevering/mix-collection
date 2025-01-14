#include <iostream>

// 指针类型的动态转换

class Base {
public:
  // 基类必需具有虚函数
  virtual ~Base() = default;
};

class Derived : public Base {
public:
  void show() { std::cout << "Derived class method" << std::endl; }
};

int main() {
    // 基类指针指向派生类对象
    Base* ptr_base = new Derived;

    // 将基类指针转换为派生类指针
    Derived* ptr_derived = dynamic_cast<Derived*>(ptr_base);

    if (ptr_derived) {
        ptr_derived->show();
    } else {
        std::cout << "Dynamic cast failed!" << std::endl;
    }

    delete ptr_base;
    return 0;
}