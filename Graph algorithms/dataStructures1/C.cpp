#include <iostream>
#include <vector>


int main() {
    int N, K;
    long long sumLen = 0;
    std::cin >> N >> K;
    std::vector<int> wires(N);
    for (int i = 0; i < N; ++i) {
        std::cin >> wires[i];
        sumLen += wires[i];
    }
    if (sumLen / K < 1) {
        std::cout << 0 << std::endl;
        return 0;
    }
    int left = 1, right = int(1e4), mid = 0;
    while (left < right) {
        mid = (left + right) / 2;
        int qnty = 0;
        for (int i = 0; i < N; ++i) {
            qnty += wires[i] / mid;
        }
        if (qnty >= K) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    std::cout << left - 1 << std::endl;
    return 0;
}