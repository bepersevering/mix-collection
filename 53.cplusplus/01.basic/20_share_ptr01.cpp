#include <iostream>
#include <memory>

class Myclass {
public:
    Myclass() {
        std::cout << "MyClass 构造函数被调用" << std::endl;
    }

    ~Myclass() {
        std::cout << "MyClass 析构函数被调用" << std::endl;
    }
    
    void show() {
        std::cout << "MyClass的show方法" << std::endl;
    }
    
};

int main() {
    std::shared_ptr<Myclass> ptr1 = std::make_shared<Myclass>();

    std::shared_ptr<Myclass> ptr2 = ptr1;

    ptr1->show();
    ptr2->show();

    std::cout << "ptr1 refrence: " << ptr1.use_count() << std::endl;
    std::cout << "ptr2 refrence: " << ptr1.use_count() << std::endl;

    return 0;
}


