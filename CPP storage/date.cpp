#include<iostream>

class Date {
    int _day, _month, _year;
public:
    Date();
    Date(const Date& other);
    friend std::ostream& operator<<(std::ostream& os, const Date& other);
    friend std::istream& operator>>(std::istream& is, Date& other);
private:
    static char const* months[12];
};
char const* Date::months[12] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
Date::Date() {}
Date::Date(const Date& other) {
    _day = other._day;
    _month = other._month;
    _year = other._year;
}
std::ostream& operator<<(std::ostream& os, const Date& other) {
    os << other._year << " " << Date::months[other._month - 1] << " " << other._day;
    return os;
}
std::istream& operator>>(std::istream& is, Date& other) {
    is >> other._year;
    is >> other._month;
    is >> other._day;
    return is;
}

int main() {
    Date i;
    std::cin >> i;
    std::cout << i << std::endl;
    return 0;
}