#include <iostream>
void test_matr();
template<class T> class matr {
    T** data;
    int str, stl;
public:
    matr(int astr, int astl) {
        str = astr;
        stl = astl;
        data = new T*[str];
        for (int i = 0; i < str; ++i) {
            T* row = new T[stl];
            for (int j = 0; j < stl; ++j)
                row[j] = 0; 
            data[i] = row;  
        }   
    }
    matr(matr<T> const& other) {
        stl = other.stl;
        str = other.str;
        data = new T*[str];
        for (int i = 0; i < str; i++) {
            T* row = new T[stl];
            for (int j = 0; j < stl; ++j) {
                row[j] = other.data[i][j];  
            }   
            data[i] = row;
        }   
    }
    ~matr() {
        for (int i = 0; i < str; ++i) {
            delete[] data[i];   
        } 
        delete[] data;  
    }   
    void print() const {
        for (int i = 0; i < str; ++i) {
            for (int j = 0; j < stl; ++j) {
                std::cout << data[i][j] << " "; 
            }
            std::cout << std::endl; 
        }   
    }
    T& operator[](int* const idx);
    T& operator[](char* const idx) const;
    matr<T> operator*(int num) const;
    matr<T>& operator=(matr<T> const& other);
    template<class U> friend matr<U> operator*(int num, matr<U> const& other);
};

template<class T> T& matr<T>::operator[](int* const idx) {
    if (idx[0] < 0 || idx[0] >= str || idx[1] < 0 || idx[1] >= stl)
        throw("Exception: Incorrect indexing");
    return data[idx[0]][idx[1]];
}

template<class T> T& matr<T>::operator[](char* const idx) const {
    throw("Exception: Incorrect indexing");
}

template<class T> matr<T> matr<T>::operator*(int num) const {
    matr<T> tmp(*this);
    for (int i = 0; i < stl; ++i) {
        for (int j = 0; j < str; ++j) {
            tmp.data[i][j] *= num;  
        }   
    }     
    return tmp;
}

template<class T> matr<T>& matr<T>::operator=(matr<T> const& other) {
    if (this == &other) return *this;
    stl = other.stl;
    str = other.str;
    for (int i = 0; i < str; ++i) {
        delete[] data[i];   
    } 
    delete[] data;
    data = new T*[str];
    for (int i = 0; i < str; i++) {
        T* row = new T[stl];
        for (int j = 0; j < stl; ++j) {
            row[j] = other.data[i][j];  
        }   
        data[i] = row;
    }
    return *this;           
}

template<class U> matr<U> operator*(int num, matr<U> const& other) {
    matr<U> tmp(other);
    for (int i = 0; i < tmp.stl; ++i) {
        for (int j = 0; j < tmp.str; ++j) {
            tmp.data[i][j] *= num;  
        }   
    } 
    return tmp;
}

int main()
{
    try {
        test_matr();    
    }
    catch(char const* exc) {
        std::cerr << exc;   
    }
    catch(...) {
        std::cerr << "Exception: incorrect indexing";   
    }
    return 0;
}