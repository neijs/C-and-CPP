#include<iostream>
#include<vector>

int split(int len, std::vector<int>& wires) {
    int res = 0;
    for (size_t i = 0; i < wires.size(); ++i) {
        res += wires[i] / len;
    }
    return res;
}

void binSearch(int amount, std::vector<int>& wires) {
    int l = 0, r = 1e4;
    int len = 0;
    while (l <= r) {
        int m = (l + r) >> 1;
        if (m == 0) {
            l = m + 1;
            continue;
        }
        int curNum = split(m, wires);
        if (curNum < amount) {
            r = m - 1;
        } else if (curNum >= amount) {
            l = m + 1;
            len = std::max(m, len);
        }
    }
    std::cout << len << std::endl;
}

int main() {
    int N, K;
    std::vector<int> wires;
    std::cin >> N >> K;
    wires.resize(N);
    for (int i = 0; i < N; ++i) {
        std::cin >> wires[i];
    }
    binSearch(K, wires);
    return 0;
}