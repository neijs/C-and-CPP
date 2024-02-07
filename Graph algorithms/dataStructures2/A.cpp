#include<iostream>
#include<vector>

class TData {
public:
    size_t index;
    int value;

    bool operator<(const TData &obj) const {
        return value < obj.value;
    }
};

class TSegmentTree {
private:
    size_t Size;
    std::vector<TData> MaxIndex;

public:
    TSegmentTree(const std::vector<TData> &src)
        : Size(src.size())
        , MaxIndex(4 * Size)
    {
        if (!src.empty()) {
            BuildTree(src, 0, 0, Size - 1);
        }
    }

    size_t FindMax(int left, int right) const {
        return FindMax(0, 0, Size - 1, left - 1, right - 1).index;
    }

    std::vector<TData> TreeInput(size_t size) const {
        std::vector<TData> source(size);
        size_t i = 0;
        for (TData &it : source) {
            std::cin >> it.value;
            it.index = i++;
        }
        return source;
    }

    void Request(size_t qnty) const {
        size_t left, right;
        for (size_t k = 0; k < qnty; ++k) {
            std::cin >> left >> right;
            std::cout << FindMax(left, right) + 1 << ' ';
        }
    }

private:
    void BuildTree(const std::vector<TData> &src, size_t index, size_t curLeft, size_t curRight) {
        if (curLeft == curRight) {
            MaxIndex[index] = src[curLeft];
        } else {
            size_t tm = curLeft + (curRight - curLeft) / 2;
            BuildTree(src, size_t(2 * index + 1), curLeft, tm);
            BuildTree(src, size_t(2 * index + 2), tm + 1, curRight);
            MaxIndex[index] = std::max(MaxIndex[size_t(2 * index + 1)], MaxIndex[size_t(2 * index + 2)]);
        }
    }

    TData FindMax(size_t index, size_t curLeft, size_t curRight, size_t left, size_t right) const {
       if (left > right || index >= 4 * Size) {
            return {0, 0};
        }
        if (curLeft == left && curRight == right) {
            return MaxIndex[index];
        }
        size_t tm = curLeft + (curRight - curLeft) / 2;
        return std::max(FindMax(size_t(2 * index + 1), curLeft, tm, left, std::min(right, tm)), 
                        FindMax(size_t(2 * index + 2), tm + 1, curRight, std::max(left, tm + 1), right));
    }
};


int main() {
    size_t N, K;
    std::cin >> N;
    TSegmentTree tree(tree.TreeInput(N));
    std::cin >> K;
    tree.Request(K);
    return 0;
}
