#include <iostream>

using namespace std;

class CDate {
public:
    CDate(int year, int month, int day);
    ~CDate();

    void show() {
        cout << "Date:" << m_year << "." << m_mon << "." << m_day << endl;

    }
private: 
    int m_year;
    int m_mon;
    int m_day;
    char *str;
};

CDate::CDate(int year, int mon, int day) {
    m_year = year;
    m_mon = mon;
    m_day = day;
    str = new char[64];
    cout << "Calling Constructor" << endl;
}

CDate::~CDate() {
    delete[] str;
    cout << "Calling Destructor" << endl;
}
