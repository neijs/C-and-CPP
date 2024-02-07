#include <iostream>
#include <cstring>

template <class T> bool maxn_cmp(T a, T b) 
    { return a > b; }

template <> bool maxn_cmp<const char*>(const char* a, const char* b) 
    { return std::strlen(a) > std::strlen(b); }

template <class T> T maxn(T* src, int len) {
    int midx = 0;
    for (int i = 1; i < len; ++i)
        if (maxn_cmp(src[i], src[midx])) midx = i;
    return src[midx];
}