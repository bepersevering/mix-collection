#include <iostream>
#include <memory>

int main() {
    std::unique_ptr<int> up(new int(10));

    std::cout << *up << std::endl;

    return 0;
}

