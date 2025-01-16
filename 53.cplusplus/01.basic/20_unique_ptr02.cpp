#include <iostream>
#include <memory>

std::unique_ptr<int> func() {
    std::unique_ptr<int> up(new int(20));
    return up;
}

int main() {
    std::unique_ptr<int> another_up = func();

    std::cout << *another_up << std::endl;

    return 0;
}

