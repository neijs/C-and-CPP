#include <iostream>
#include <cmath>
#include "Quotient.h"
int Quotient::gcd(unsigned x, unsigned y) {
    if (y == 0)
        return x;
    return gcd(y, x % y);
}

Quotient::Quotient(int arg_n, unsigned arg_d) {
    int gcd_val;
    if (arg_d == 0)
        arg_d = 1;
    else if (int(arg_d) < 0) {
        arg_d = unsigned(int(arg_d) * -1);
        arg_n *= -1;
    }
    gcd_val = gcd(abs(arg_n), arg_d);
    numer = int(arg_n / gcd_val);
    denom = unsigned(arg_d / gcd_val);
}
Quotient::Quotient() {
    numer = 0;
    denom = 1;
}
Quotient::Quotient(int arg_n) {
    numer = arg_n;
    denom = 1;
}
void Quotient::print() {
    if (denom == 1) 
        std::cout << numer << std::endl;
    else
        std::cout << numer << "/" << denom << std::endl;
}
