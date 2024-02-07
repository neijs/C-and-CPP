#include<iostream>
#include<vector>

class TSegmentTree {
private:
    uint64_t Size;
    std::vector<uint64_t> Sum;

public:
    TSegmentTree(const std::vector<uint64_t> &src)
        : Size(src.size())
        , Sum(4 * Size)
    {
        if (!src.empty()) {
            BuildTree(src, 0, 0, Size - 1);
        }
    }

    uint64_t FindSum(uint64_t left, uint64_t right) const {
        return FindSum(0, 0, Size - 1, left - 1, right - 1);
    }

    void Update(uint64_t pos, int newValue) {
        Update(0, 0, Size - 1, pos - 1, newValue);
    }

    std::vector<uint64_t> TreeInput(uint64_t size) const {
        std::vector<uint64_t> source(size);
        for (auto &it : source) {
            std::cin >> it;
        }
        return source;
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
    void BuildTree(const std::vector<uint64_t> &src, uint64_t index, uint64_t curLeft, uint64_t curRight) {
        if (curLeft == curRight) {
            Sum[index] = src[curLeft];
        } else {
            uint64_t mid = curLeft + (curRight - curLeft) / 2;
            BuildTree(src, uint64_t(2 * index + 1), curLeft, mid);
            BuildTree(src, uint64_t(2 * index + 2), mid + 1, curRight);
            Sum[index] = Sum[uint64_t(2 * index + 1)] + Sum[uint64_t(2 * index + 2)];
        }
    }

    uint64_t FindSum(uint64_t index, uint64_t curLeft, uint64_t curRight, uint64_t left, uint64_t right) const {
       if (left > right || index >= 4 * Size) {
            return 0;
        }
        if (curLeft == left && curRight == right) {
            return Sum[index];
        }
        uint64_t mid = curLeft + (curRight - curLeft) / 2;
        return FindSum(uint64_t(2 * index + 1), curLeft, mid, left, std::min(right, mid)) +
               FindSum(uint64_t(2 * index + 2), mid + 1, curRight, std::max(left, mid + 1), right);
    }

    void Update(uint64_t index, uint64_t curLeft, uint64_t curRight, uint64_t pos, int newValue) {
        if (curLeft == curRight) {
            Sum[index] = newValue;
        } else {
            uint64_t mid = curLeft + (curRight - curLeft) / 2;
            if (pos > mid) {
                Update(uint64_t(2 * index + 2), mid + 1, curRight, pos, newValue);
            } else {
                Update(uint64_t(2 * index + 1), curLeft, mid, pos, newValue);
            }
            Sum[index] = Sum[uint64_t(2 * index + 1)] + Sum[uint64_t(2 * index + 2)];
        }
    }
};

int main() {
    uint64_t N, M;
    std::cin >> N;
    TSegmentTree tree(tree.TreeInput(N));
    std::cin >> M;
    tree.Request(M);
    return 0;
}
