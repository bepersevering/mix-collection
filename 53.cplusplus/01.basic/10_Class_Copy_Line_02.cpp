#include <iostream>

using namespace std;

class Line {
public:
    int getLength(void);
    Line(int len);  // simple constructor 
    Line(const Line &obj); // copy constructor
    ~Line();

private:
    int *ptr;
};

// 成员函数定义，包括构造函数
Line::Line(int len) {
    cout << "调用构造函数" << endl;
    // 为指针分配内存
    ptr = new int;
    *ptr = len;
}

Line::Line(const Line &obj) {
    cout << "调用拷贝构造函数并为指针 ptr 分配内存" << endl;

    ptr = new int;
    *ptr = *obj.ptr; // copy pointer
}

Line::~Line() {
    delete ptr;
}


int Line::getLength(void) {
    return *ptr;
}

void display(Line obj) {
    cout << "Line = : " << obj.getLength() << endl;
}

int main() {
    Line line1(10);
    Line line2 = line1;

    display(line1);
    display(line2);

    return 0;
}


