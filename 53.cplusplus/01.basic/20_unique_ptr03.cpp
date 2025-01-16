#include <iostream>
#include <memory>


void customer_deleter(int* p) {
    std::cout << "Customer deletion" << std::endl;
    delete p;
}


int main() {
    std::unique_ptr<int, void(*)(int*)> up(new int(20), customer_deleter);

    std::cout << *up<< std::endl;

    return 0;
}

