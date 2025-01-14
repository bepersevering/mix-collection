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

int main() { 
    Derived derived_obj;
    Base &ref_base = derived_obj;

    try {
        // 将基类引用转换为派生对象
        Derived& ref_derived = dynamic_cast<Derived&> (ref_base);
        ref_derived.show(); //成功转换，调用派生类方法

    } catch (const std::bad_cast& e) {
        std::cout << "Dynamic cast failed: " << e.what() << std::endl;
    }
    
    return 0; 
}
