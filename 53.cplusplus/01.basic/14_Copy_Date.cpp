#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

#define MAX_NEW_MEM (64 * 1000 * 1000)

class CDate {
public:
    CDate(int year, int mon, int day);

    CDate(const CDate &date);
    ~CDate();

    CDate operator+(int day);

    void show() {
        cout << "Date: " << m_year << "." << m_mon << "." << m_day << ", this=" << this << endl;
    }

private:
    int m_year;
    int m_mon;
    int m_day;
    char *str;

};

// 构造函数
CDate::CDate(int year, int mon, int day) {
    m_year = year;
    m_mon = m_mon;
    m_day = day;
    str = new char[MAX_NEW_MEM];

    sprintf(str, "%4d.%02d.%02d", year, mon, day);

    cout << "Calling Constructor" << ", this=" << this << endl;
}


CDate::CDate(const CDate &date) {
    m_year = date.m_year;
    m_mon = date.m_mon;
    m_day = date.m_day;
    str = new char[MAX_NEW_MEM];

    memcpy(str, date.str, MAX_NEW_MEM);

    cout << "Calling Copy Constructor" << ", this=" << this << endl;
}

CDate::~CDate() {
    cout << "Calling Destructor" << ", this=" << this << endl;
    delete[] str;
}


CDate CDate::operator+(int day) {
    CDate temp = *this;
    temp.m_day += day;

    cout << "Calling operator+" << ", this=" << this << endl;
    return temp;

}


int main() {
    CDate date(2024, 12, 11);
    cout << endl;

    CDate date1 = std::move(date + 1);
    date1.show();

    cout << endl;

    return 0;
}

