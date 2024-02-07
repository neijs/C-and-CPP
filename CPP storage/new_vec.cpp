#include <iostream>
#include <cmath>
using namespace std;

class Vec {
    double *v;
    int len;
    public:
        Vec(int len, double *v);
        Vec(int len);
        Vec(const Vec &arg);
        ~Vec();
        void set(double arg, int coord);
        double get(int coord) const;
        double euc_norm() const;
        double max_norm() const; 
        void print() const;

        Vec operator+(const Vec &other) const;
        Vec operator-(const Vec &other) const;
        Vec operator*(double num) const;
        Vec& operator=(const Vec &other);
        bool operator==(const Vec &other) const;
        double& operator[](int index);
        friend ostream& operator<<(ostream& os, const Vec &other);
        friend Vec operator*(double num, const Vec &other);
};
Vec::Vec(int len, double *v) {
    this -> len = len;
    this -> v = new double[len];
    for (int i = 0; i < len; i++)
        (this -> v)[i] = v[i];
}
Vec::Vec(int len) {
    this -> len = len;
    v = new double[len];
    for (int i = 0; i < len; i++)
        v[i] = 0.0;
}
Vec::Vec(const Vec &arg) {
    len = arg.len;
    v = new double[len];
    for (int i = 0; i < len; i++)
        v[i] = arg.v[i];
}
Vec::~Vec() {
    delete[] v;
}
void Vec::set(double arg, int coord) {
    if (coord > len - 1 || coord < 0)
        return;
    v[coord] = arg;
}
double Vec::euc_norm() const {
    double sum = 0;

    for (int i = 0; i < len; i++)
        sum += pow(v[i], 2);
    return sqrt(sum);
}
double Vec::get(int coord) const {
    if (coord > len - 1 || coord < 0)
        return 0;
    return v[coord];
}
double Vec::max_norm() const {
    double max = fabs(v[0]);
    for (int i = 1; i < len; i++) {
        if (fabs(v[i]) > max)
            max = fabs(v[i]);
    }  
    return max; 
}
void Vec::print() const {
    cout << "(";
    for (int i = 0; i < len; i++) {
        cout << v[i];
        if (i != len - 1) 
            cout << ",";
    } 
    cout << ")" << endl;
}
Vec Vec::operator+(const Vec &other) const {
    Vec tmp = *this;
    for (int i = 0; i < len; i++)
       tmp.v[i] += other.v[i]; 
    return tmp;
}
Vec Vec::operator-(const Vec &other) const {
    Vec tmp = *this;
    for (int i = 0; i < len; i++)
       tmp.v[i] -= other.v[i]; 
    return tmp;
}
Vec Vec::operator*(double num) const {
    Vec tmp = *this;
    for (int i = 0; i < len; i++)
        tmp.v[i] *= num;
    return tmp;
}
Vec& Vec::operator=(const Vec &rhs) {
    if (this == &rhs) return *this;
    len = rhs.len;
    delete[] v;
    v = new double[len];
    for (int i = 0; i < len; i++)
        v[i] = rhs.v[i];
    return *this;
}
bool Vec::operator==(const Vec &other) const {
    if (len != other.len)
        return false;
    for (int i = 0; i < len; i++)
        if (v[i] != other.v[i])
            return false;
    return true;
}
double& Vec::operator[](int index) {
    return v[index];
}
ostream& operator<<(ostream& os, const Vec &src) {
    os << "(";
    for (int i = 0; i < src.len; i++) {
        os << src.v[i];
        if (i != src.len - 1) 
            os << ",";
    } 
    os << ")";
    return os;
}
Vec operator*(double num, const Vec &other) {
    Vec tmp = other;
    for (int i = 0; i < other.len; i++)
        tmp.v[i] *= num;
    return tmp;
}