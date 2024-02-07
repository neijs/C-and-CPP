#include<iostream>
#include<vector>

class TFenwickTree {
private:
    int64_t Size;
    std::vector<uint64_t>& Source;
    std::vector<uint64_t> Tree;

public:
    TFenwickTree(std::vector<uint64_t>& src)
        : Size(src.size())
        , Source(src)
        , Tree(Size)
    {
        for (int64_t i = 0; i < Size; ++i) {
            Collerate(i, src[i]);
        }
    }

    uint64_t FindSum(int64_t left, int64_t right) const {
        return FindSum(right - 1) - FindSum(left - 2);
    }

    void Update(int64_t index, uint64_t newValue) {
        Collerate(index - 1, (newValue - Source[index - 1]));
        Source[index - 1] = newValue;
    }

    void Request(uint64_t qnty) {
        for (uint64_t m = 0; m < qnty; ++m) {
            while (isspace(std::cin.peek())) {
                std::cin.get();
            }
            char cmd = std::cin.get();
            switch (cmd) {
            case 's':
                int left, right;
                std::cin >> left >> right;
                std::cout << FindSum(left, right) << ' ';
                break;
            case 'u':
                int pos, value;
                std::cin >> pos >> value;
                Update(pos, value);
                break;
            default:
                break;
            }
        }
    }

private:
    void Collerate(int64_t index, int64_t delta) {
        for (int64_t i = index; i < Size; i = i | (i + 1)) {
            Tree[i] += delta;
        }
    }

    uint64_t FindSum(int64_t index) const {
        if (index < 0) {
            return 0;
        }
        uint64_t sum;
        for (sum = 0; index >= 0; index = (index & (index + 1)) - 1) {
            sum += Tree[index];
        }
        return sum;
    }
};

std::vector<uint64_t> Input(uint64_t size) {
    std::vector<uint64_t> source(size);
    for (auto &it : source) {
        std::cin >> it;
    }
    return source;
}

int main() {
    uint64_t N, M;
    std::cin >> N;
    std::vector<uint64_t> source = Input(N);
    TFenwickTree tree(source);
    std::cin >> M;
    tree.Request(M);
    return 0;
}