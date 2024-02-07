#include <iostream>
#include <cstring>
#include <cmath>

template <typename U> void sort(U* const data, int amount) {
    bool sorted = false;
    while (!sorted) {
        sorted = true;
        for (int j = 0; j < amount - 1; ++j) {
            if (data[j] > data[j + 1]) {
                U temp = data[j];
                data[j] = data[j + 1];
                data[j + 1] = temp;
                sorted = false;
            }
        }
    }
}

template <class T> class Set {
    T* _data;
    size_t _size;
    int _count;
public:
    Set() : _data(nullptr), _size(0), _count(0) {}
    Set(T const* data, int amount);
    Set(Set<T> const& other);
    ~Set() { delete[] _data; }
    void add(T elem);
    void add(T const* elems, int amount);
    void del(T elem);
    bool in(T elem) const;
    void print() const;
    Set<T> const& operator=(Set<T> const& other);
    Set<T> operator*(Set<T> const& other) const;
    Set<T> operator+(Set<T> const& other) const;
private:
    void realloc(int add_on);
    template <typename U> friend void sort(U* const data, int amount);
};

template <class T> Set<T>::Set(T const* data, int amount) : _count(0) {
    T* tmp = new T[amount];
    for (int i = 0; i < amount; tmp[i] = data[i], ++i);
    sort<T>(tmp, amount);
    _data = new T[_size = amount];
    for (int i = 0; i < amount; ++i)
        if (!in(tmp[i])) _data[_count++] = tmp[i];
    delete[] tmp;
}

template <class T> Set<T>::Set(Set<T> const& other) {
    _data = new T[_size = other._size];
    for (int i = 0; i < (_count = other._count); ++i)
        _data[i] = other._data[i];
}

template <class T> void Set<T>::add(T elem) {
    if (in(elem)) return;
    realloc(1);
    _data[_count++] = elem;
    sort<T>(_data, _count);
}

template <class T> void Set<T>::add(T const* elems, int amount) {
    for (int i = 0; i < amount; ++i) add(elems[i]);
}

template <class T> void Set<T>::del(T elem) {
    if (!in(elem)) return;
    int i; --_count;
    for (i = 0; _data[i] != elem; ++i);
    for (int j = i; j < _count; ++j)
        _data[j] = _data[j + 1]; 
}

template <class T> bool Set<T>::in(T elem) const {
    int left = 0, right = _count - 1, mid;
    if (_count == 0) return false;
    while (left <= right) {
        mid = left + floor( (right - left)/2 );
        if(_data[mid] == elem)
            return true;
        if (_data[mid] < elem) left = mid + 1;
        else right = mid - 1;
    }
    return false;
}

template <class T> void Set<T>::print() const {
    for (int i = 0; i < _count; ++i)
        std::cout << _data[i] << " ";
    std::cout << std::endl;
}

template <class T> Set<T> const& Set<T>::operator=(Set<T> const& other) {
    if (this == &other) return *this;
    delete[] _data;
    _data = new T[_size = other._size];
    for (int i = 0; i < (_count = other._count); ++i)
        _data[i] = other._data[i];
    return *this;
}

template <class T> Set<T> Set<T>::operator*(Set<T> const& other) const {
    Set<T> tmp;
    for (int i = 0; i < _count; ++i)
        if (other.in(_data[i])) tmp.add(_data[i]);
    return tmp;
}

template <class T> Set<T> Set<T>::operator+(Set<T> const& other) const {
    Set<T> tmp(*this);
    tmp.add(other._data, other._count);
    return tmp;
}

template <class T> void Set<T>::realloc(int add_on) {
    if ((_count + add_on) * sizeof(T) <= _size) return;
    while ((_count + add_on) * sizeof(T) > _size) {
        if (_size == 0) _size = sizeof(T);
        _size *= 2;
    }
    T* tmp = new T[_size];
    if (_data != nullptr) {
        std::memcpy(tmp, _data, _size);
        delete[] _data;
    }
    _data = tmp;
}