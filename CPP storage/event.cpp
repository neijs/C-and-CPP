#include <iostream>
#include <cstring>
class event {
    char* _subj;
    int _day, _month, _year;
public:
    event(const char* subj, int year, int month, int day);
    virtual ~event();
    virtual void print_res() const;
    virtual void change_date(int new_year, int new_month, int new_day);
    virtual void change_grade(bool) {}
    virtual void change_grade(int) {}
};

class test : public event {
    bool _passed;
public:
    test(const char* subj, int year, int month, int day, bool passed);
    void print_res() const;
    void change_grade(bool new_grade);
};

class exam : public event {
    int _grade;
public:
    exam(const char* subj, int year, int month, int day, int grade);
    void print_res() const;
    void change_grade(int new_grade);
};

event::event(const char* subj, int year, int month, int day) {
    size_t size = std::strlen(subj) + 1;
    _subj = new char[size];
    std::memcpy(_subj, subj, size);
    _day = day;
    _month = month;
    _year = year;
}

event::~event() {
    delete[] _subj;
}

void event::print_res() const {
    std::cout << _subj << " " << _year << " " << _month << " " << _day << " ";
}

void event::change_date(int new_year, int new_month, int new_day) {
    _day = new_day;
    _month = new_month;
    _year = new_year;
}

test::test(const char* subj, int year, int month, int day, bool passed) : event(subj, year, month, day), _passed(passed) 
    {}

void test::print_res() const {
    event::print_res();
    if (_passed) std::cout << "true" << std::endl;
    else std::cout << "false" << std::endl;
}

void test::change_grade(bool new_grade) {
    _passed = new_grade;
}

exam::exam(const char* subj, int year, int month, int day, int grade) : event(subj, year, month, day), _grade(grade) 
    {}

void exam::print_res() const {
    event::print_res();
    std::cout << "Grade " << _grade << std::endl;
}

void exam::change_grade(int new_grade) {
    _grade = new_grade;
}