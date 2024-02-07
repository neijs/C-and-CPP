#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cstdlib>

class Matrix {
    std::vector<std::vector<int>> _data;
    std::vector<int> _excess; //used only in irb ira icb ica
    int _rows, _cols;
public:
    Matrix();
    void irb(int num);
    void ira(int num);
    void icb(int num);
    void ica(int num);
    void dr(int num);
    void dc(int num);
    void sr(int num1, int num2);
    void sc(int num1, int num2);
    void t();
    void print() const;
};

int main(int argc, char** argv) {
    Matrix matrix;
    int num1, num2;
    if (argc == 1) { matrix.print(); return 0; }
    std::string cmd(argv[1]);
    if (argc == 4) {
        num1 = int(std::strtol(argv[2], NULL, 10));
        num2 = int(std::strtol(argv[3], NULL, 10));
        if (cmd == "-sr")       matrix.sr(num1, num2);
        else if (cmd == "-sc")  matrix.sc(num1, num2);
    } else if (argc == 3) {
        num1 = int(std::strtol(argv[2], NULL, 10));
        if (cmd == "-irb")      matrix.irb(num1);
        else if (cmd == "-ira") matrix.ira(num1);
        else if (cmd == "-icb") matrix.icb(num1);
        else if (cmd == "-ica") matrix.ica(num1);
        else if (cmd == "-dr")  matrix.dr(num1);
        else if (cmd == "-dc")  matrix.dc(num1);
    } else if (argc == 2 && cmd == "-t") { matrix.t(); }
    matrix.print();
    return 0;
}

Matrix::Matrix() {
    std::string string;
    std::getline(std::cin, string);
    std::stringstream sstr(string);
    sstr >> _rows >> _cols;
    for (int i = 0; i < _rows; ++i) {
        std::vector<int> row;
        for (int j = 0; j < _cols; ++j) {
            int elem; sstr >> elem;
            row.push_back(elem);
        }
        _data.push_back(row);
    }
    int n;
    while (sstr >> n)
        _excess.push_back(n);
}

void Matrix::irb(int num) {
    if (num < 1 || num > _rows) return;
    _data.insert(_data.begin() + num - 1, _excess);
    ++_rows;
}

void Matrix::ira(int num) {
    if (num < 1 || num > _rows) return;
    _data.insert(_data.begin() + num, _excess);
    ++_rows;
}

void Matrix::icb(int num) {
    if (num < 1 || num > _cols) return;
    t(); irb(num); t();
}

void Matrix::ica(int num) {
    if (num < 1 || num > _cols) return;
    t(); ira(num); t();
}

void Matrix::dr(int num) {
    if (num < 1 || num > _rows) return;
    _data.erase(_data.begin() + num - 1);
    --_rows;
}

void Matrix::dc(int num) {
    if (num < 1 || num > _cols) return;
    t(); dr(num); t();
    
}

void Matrix::sr(int num1, int num2) {
    if (num1 < 1 || num1 > _rows || num2 < 1 || num2 > _rows) return;
    auto iter1 = _data.begin() + num1 - 1;
    auto iter2 = _data.begin() + num2 - 1;
    std::vector<int> tmp(*iter1);
    *iter1 = *iter2;
    *iter2 = tmp; 
}

void Matrix::sc(int num1, int num2) {
    if (num1 < 1 || num1 > _cols || num2 < 1 || num2 > _cols) return;
    t(); sr(num1, num2); t();
}

void Matrix::t() {
    std::vector<std::vector<int>> tmp;
    for (int i = 0; i < _cols; ++i) {
        std::vector<int> row;
        for (auto iter = _data.begin(); iter != _data.end(); ++iter)
            row.push_back(*((*iter).begin() + i));
        tmp.push_back(row);
    }
    int n = _rows;
    _rows = _cols;
    _cols = n;
    _data = tmp;
}

void Matrix::print() const {
    for (auto row_iter = _data.begin(); row_iter != _data.end(); ++row_iter) {
        for (auto col_iter = (*row_iter).begin(); col_iter != (*row_iter).end(); ++col_iter)
            std::cout << *col_iter << ' ';
        std::cout << std::endl;
    }
}