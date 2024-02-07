#include <iostream>
#include <vector>


void Heap(std::vector<int>& array, int index, int size) {
    int max = index;
    while (true) {
        int child = 2 * index + 1;
        if (child < size && array[child] > array[max])
            max = child;
        child++;
        if (child < size && array[child] > array[max])
            max = child;
        if (max == index)
            break;
        else {
            std::swap(array[max], array[index]);
            index = max;
        }
    }
}

void HeapSort(std::vector<int>& array, int size) {
    for (int i = size / 2; i >= 0; --i)
        Heap(array, i, size);
    for (int i = size - 1; i >= 1; --i) {
        std::swap(array[0], array[i]);
        Heap(array, 0, i);
    }
}

void HeapInput(std::vector<int>& array, int& size) {
    std::cin >> size;
    array.resize(size);
    for (int i = 0; i < size; ++i) {
        std::cin >> array[i];
    }
}

void HeapOutput(std::vector<int>& array, int& size) {
    std::vector<int> s;
    if (size == 2) {
        std::cout << array[1] - array[0];
        return;
    }
    s.push_back(array[1] - array[0]);
    s.push_back(array[2] - array[0]);
    for (int i = 2; i < size - 1; ++i)
        s.push_back(std::min(s[i - 1], s[i - 2]) + array[i + 1] - array[i]);
    std::cout << s[size - 2];
}

int main() {
    int size;
    std::vector<int> array;
    HeapInput(array, size);
    HeapSort(array, size);
    HeapOutput(array, size);
    return 0;
}