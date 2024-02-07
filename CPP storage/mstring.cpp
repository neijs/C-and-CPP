#include <iostream>
#include <cstring>
class _exception {
    char* _name;
    int _arg1, _arg2;
    bool _flag;
public:
    _exception(const char* name, int arg1 = 0, int arg2 = 0, bool flag = false);
    ~_exception();
    void what() const;
};
class mstring {
    char* _Str;
    size_t _Size;
public:
    mstring();
    mstring(const mstring& other);
    mstring(const char* src);
    ~mstring();
    int length() const;
    bool isempty() const;
    void add(char c);
    void add(const char* c);
    void insert(char c, int i);
    void insert(const char* c, int i);
    void del(int i);
    void del(int i, int j);
    int search(const char* str) const;
    void replace(const char* sub_str, const char* new_str);
    void print() const;

    mstring operator*(int n) const;
    mstring& operator=(const mstring& other);
    bool operator>(const mstring& other) const;
    bool operator<(const mstring& other) const;
    bool operator>=(const mstring& other) const;
    bool operator<=(const mstring& other) const;
    bool operator==(const mstring& other) const;
    char& operator[](int index);

    friend std::ostream& operator<<(std::ostream& os, const mstring& other);
    friend std::istream& operator>>(std::istream& is, mstring& other);
    friend mstring operator*(int n, const mstring& other);
    friend mstring operator+(const mstring& lhs, const mstring& rhs);
private:
    void realloc(size_t size);
};
void error();

mstring::mstring() { // default
    _Size = 1;
    _Str = new char('\0');
}

mstring::mstring(const mstring& other) { // copy
    _Str = new char[_Size = other._Size];
    std::memcpy(_Str, other._Str, _Size);
} 

mstring::mstring(const char *src) { // conversion
    _Str = new char[_Size = std::strlen(src) + 1];
    std::memcpy(_Str, src, _Size);
}   

mstring::~mstring() { // destructor
    delete[] _Str;
}

int mstring::length() const { // '\0' is not counted
    return std::strlen(_Str);
}

bool mstring::isempty() const {
    return *_Str == '\0';
}

void mstring::add(const char *c) {
    realloc(_Size + std::strlen(c));
    std::strcat(_Str, c);
}

void mstring::add(char c) {
    char* tmp = new char[2];
    tmp[0] = c; tmp[1] = '\0';
    const char* ctmp = tmp;
    add(ctmp);
    delete[] tmp;
}

void mstring::insert(char c, int i) {
    if (i < 0 || i > length()) throw _exception("insert", i);
    realloc(_Size + 1);
    for (int ind = _Size - 1; ind > i; ind--) 
        _Str[ind] = _Str[ind - 1];
    _Str[i] = c;
}

void mstring::insert(const char *c, int i) {
    if (i < 0 || i > length()) throw _exception("insert", i);
    realloc(_Size + std::strlen(c));
    for (int j = 0; j < std::strlen(c); j++) {
        for (int ind = _Size - 1; ind > i; ind--) 
            _Str[ind] = _Str[ind - 1];
        _Str[i++] = c[j];
    }
}

void mstring::del(int i, int j) {
    if (i < 0 || j >= length() || i > j) throw _exception("del", i, j, true);
    for (int k = i; k <= j; k++)
        for (int ind = i + 1; ind < _Size; ind++)
            _Str[ind - 1] = _Str[ind];
    realloc(_Size - (j - i + 1));
}

void mstring::del(int i) {
    if (i < 0 || i >= length()) throw _exception("del", i);
    del(i, i);
}

int mstring::search(const char *str) const {
    const char* ptr = std::strstr(_Str, str);
    if (ptr == nullptr) return -1;
    return ptr - _Str;
}

void mstring::replace(const char *sub_str, const char *new_str) {
    int coord = search(sub_str);
    if (coord == -1) return;
    if (*sub_str != '\0') del(coord, coord + std::strlen(sub_str) - 1); //delete the sub_str
    insert(new_str, coord);
}

void mstring::print() const {
    std::cout << _Str << std::endl;
}

void mstring::realloc(size_t desired_size) {
    char *tmp = new char[_Size = desired_size];
    std::memcpy(tmp, _Str, _Size);
    delete[] _Str;
    _Str = tmp;
}

mstring operator+(const mstring &lhs, const mstring &rhs) {
    mstring res(lhs);
    res.add(rhs._Str);
    return res;
}

mstring mstring::operator*(int n) const {
    if (n < 0) throw _exception("operator*", n);
    if (!n) return mstring();
    mstring lhs(*this);
    for (int i = 1; i < n; i++)
        lhs.add(_Str);
    return lhs;
}

mstring operator*(int n, const mstring& other) {
    if (n < 0) throw _exception("operator*", n);
    if (!n) return mstring();
    mstring lhs(other);
    for (int i = 1; i < n; i++)
        lhs.add(other._Str);
    return lhs;
}

mstring& mstring::operator=(const mstring &other) {
    if (this == &other) return *this;
    delete[] _Str;
    _Str = new char[_Size = other._Size];
    std::memcpy(_Str, other._Str, _Size);
    return *this;    
}

bool mstring::operator>(const mstring &other) const {
    return (std::strcmp(_Str, other._Str) > 0) ? true : false;
}

bool mstring::operator<(const mstring &other) const {
    return (std::strcmp(_Str, other._Str) < 0) ? true : false;
}

bool mstring::operator>=(const mstring &other) const {
    return !(*this < other);
}

bool mstring::operator<=(const mstring &other) const {
    return !(*this > other);
}

bool mstring::operator==(const mstring &other) const {
    return !std::strcmp(_Str, other._Str);
}

char& mstring::operator[](int index) { // can't access '\0'
    if (index >= 0 && index < length()) return _Str[index];
    throw _exception("operator[]", index);
}

std::ostream& operator<<(std::ostream& os, const mstring &other) {
    os << other._Str;
    return os;
}

std::istream& operator>>(std::istream& is, mstring &other) {
    char c;
    other = mstring();
    if (is.eof()) return is;
    is >> std::noskipws >> c;
    while ((c != '\n') && !is.eof()) {
        other.add(c);
        is >> c;
    }
    return is;
}

int main() {
    try {
        error();
    }
    catch(const _exception& e) {
        e.what();
    }
    return 0;
}

_exception::_exception(const char* name, int arg1, int arg2, bool flag) {
    size_t len = std::strlen(name) + 1;
    _name = new char[len];
    std::memcpy(_name, name, len);
    _arg1 = arg1;
    _arg2 = arg2;
    _flag = flag;
}

_exception::~_exception() {
    delete[] _name;
}
void _exception::what() const {
    std::cerr << "Exception: problem in " << _name << " incorrect parameter:";
    if (_flag) std::cerr << _arg1 << " " << _arg2 << std::endl;
    else std::cerr << _arg1 << std::endl;
}