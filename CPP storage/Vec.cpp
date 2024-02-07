#include <iostream>
#include <cmath>
#include <cstring>

void Vector();

class def_exc {
    char* _msg;
public:
    def_exc();
    def_exc(char const* src) { _msg = strdup(src); }
    virtual void what() const {
        std::cerr << _msg;
    }
    virtual ~def_exc() { delete[] _msg; }
protected:
    static char* strdup(char const* str) {
        char* res = new char[std::strlen(str) + 1];
        std::strcpy(res, str);
        return res;
    }
};

class arg1_exc : public def_exc {
    char* _msg;
    int _arg1;
public:
    arg1_exc();
    arg1_exc(char const* src, int arg1) : def_exc(src) 
        { _arg1 = arg1; }
    virtual void what() const {
        def_exc::what();
        std::cerr << _arg1;
    }
    virtual ~arg1_exc() { delete[] _msg; }
};

class arg2_exc : public arg1_exc {
    char* _msg;
    int _arg1, _arg2;
public:
    arg2_exc(char const* src, int arg1, int arg2) : arg1_exc(src, arg1) 
        { _arg2 = arg2; }
    virtual void what() const {
        arg1_exc::what();
        std::cerr << " " << _arg2; 
    }
    virtual ~arg2_exc() { delete[] _msg; }
};

template <class T> class Vec {
    T* _v;
    int _len;
    public:
        Vec(int len, T* v);
        Vec(int len);
        Vec(Vec<T> const& arg);
        ~Vec() { delete[] _v; };
        void set(T arg, int coord);
        T get(int coord) const;
        T max_norm() const;
        Vec<T> operator+(Vec<T> const& other) const;
        Vec<T> operator-(Vec<T> const& other) const;
        Vec<T> operator*(double num) const;
        T operator^(Vec<T> const& other) const;
        Vec<T>& operator=(Vec<T> const& other);
        Vec<T>& operator+=(Vec<T> const& other);
        bool operator==(Vec<T> const& other) const;
        T& operator[](int index);
        template <class U> friend std::ostream& operator<<(std::ostream& os, Vec<U> const& other);
        template <class U> friend Vec<U> operator*(double num, Vec<U> const& other);
};

template <class T> Vec<T>::Vec(int len, T* v) {
    if (len <= 0) throw def_exc("Exception: length error");
    _v = new T[_len = len];
    for (int i = 0; i < len; ++i)
        _v[i] = v[i];
}

template <class T> Vec<T>::Vec(int len) {
    if (len <= 0) throw def_exc("Exception: length error");
    _v = new T[_len = len];
    for (int i = 0; i < len; ++i)
        _v[i] = 0.0;
}

template <class T> Vec<T>::Vec(Vec<T> const& other) {
    _v = new T[_len = other._len];
    for (int i = 0; i < _len; ++i)
        _v[i] = other._v[i];
}

template <class T> void Vec<T>::set(T arg, int coord) {
    if (coord >= 0 && coord <= (_len - 1)) _v[coord] = arg; 
    else throw def_exc("Exception: coordinate error in set()");
}

template <class T> T Vec<T>::get(int coord) const {
    if (coord >= 0 && coord <= (_len - 1)) return _v[coord];
    throw def_exc("Exception: coordinate error in get()");
}

template <class T> T Vec<T>::max_norm() const {
    T max = fabs(_v[0]);
    for (int i = 1; i < _len; ++i)
        if (fabs(_v[i]) > max) max = fabs(_v[i]);
    return max; 
}

template <class T> Vec<T> Vec<T>::operator+(Vec<T> const& other) const {
    if (_len != other._len) 
        throw arg2_exc("Exception: addition of vectors of different lengths: ", _len, other._len);
    Vec<T> tmp(*this);
    for (int i = 0; i < _len; ++i)
       tmp._v[i] += other._v[i]; 
    return tmp;
}

template <class T> Vec<T> Vec<T>::operator-(Vec<T> const& other) const {
    if (_len != other._len)
        throw arg2_exc("Exception: addition of vectors of different lengths: ", _len, other._len);
    Vec<T> tmp(*this);
    for (int i = 0; i < _len; ++i)
       tmp._v[i] -= other._v[i]; 
    return tmp;
}

template <class T> Vec<T> Vec<T>::operator*(double num) const {
    Vec<T> tmp(*this);
    for (int i = 0; i < _len; ++i)
        tmp._v[i] *= num;
    return tmp;
}

template <class T> T Vec<T>::operator^(Vec<T> const& other) const {
    if (_len != other._len)
        throw arg2_exc("Exception: multiplication of vectors of different lengths: ", _len, other._len);
    T dot_product = 0;
    for (int i = 0; i < _len; ++i)
        dot_product += _v[i] * other._v[i];
    return dot_product;
}
template <class T> Vec<T>& Vec<T>::operator=(Vec<T> const& rhs) {
    if (this == &rhs) return *this;
    _len = rhs._len;
    delete[] _v;
    _v = new T[_len];
    for (int i = 0; i < _len; ++i)
        _v[i] = rhs._v[i];
    return *this;
}

template <class T> Vec<T>& Vec<T>::operator+=(Vec<T> const& other) {
    *this = *this + other;
    return *this;
}

template <class T> bool Vec<T>::operator==(Vec<T> const& other) const {
    if (_len != other._len) return false;
    for (int i = 0; i < _len; ++i)
        if (_v[i] != other._v[i])
            return false;
    return true;
}

template <class T> T& Vec<T>::operator[](int index) {
    if (index >= 0 && index <= _len - 1) return _v[index];
    throw arg1_exc("Exception: incorrect indexing: ", index);
}

template <class U> std::ostream& operator<<(std::ostream& os, Vec<U> const& src) {
    os << "(";
    for (int i = 0; i < src._len; ++i) {
        os << src._v[i];
        if (i != src._len - 1) os << ",";
    } 
    os << ")";
    return os;
}

template <class U> Vec<U> operator*(double num, Vec<U> const& other) {
    Vec<U> tmp = other;
    for (int i = 0; i < other._len; ++i)
        tmp._v[i] *= num;
    return tmp;
}

int main() {
    try {
        Vector();
    }
    catch(def_exc const& exc) {
        exc.what();
    }
    catch(...) {
        std::cerr << "Exception: unknown error";
    }
    return 0;
}