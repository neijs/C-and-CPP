#include<iostream>
#include<complex>
#include<cmath>

const unsigned N = 11;

double fj(unsigned j, double a, double tau, double h) {
    if (1 <= j  && j <= N / 2 + 1) {
        return 2.0 * a * h * (j - 1) / 1.0 * tau;
    } else {
        return 2.0 * a * (tau - h * j + h) / 1.0 * tau;
    }
}
 
int main() {
    double a = 1.0;
    double tau = 1.0;
    double h = tau / N;

    std::complex<double> i (0.0, 1.0);

    for (unsigned n; n <= N + 1; ++n) {
        std::complex<double> Sh = 0;
        for (unsigned j = 1; j <= N + 1; ++j) {
            std::complex<double> W = std::exp(2 * M_PI * i / N);
        }
    }
    return 0;
}