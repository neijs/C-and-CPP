#include<iostream>
#include<vector>

class TData {
public:
    uint64_t Value, Delta;
    
    bool operator<(const TData &obj) const {
        return (Value + Delta) < (obj.Delta + obj.Value);
    }
};

class TSegmentTree {
private:
    uint64_t Size;
    std::vector<TData> Tree;

public:
    TSegmentTree(const std::vector<uint64_t> &src)
        : Size(src.size())
        , Tree(4 * Size)
    {
        if (!src.empty()) {
            BuildTree(src, 0, 0, Size - 1);
        }
    }

    uint64_t FindMax(uint64_t left, uint64_t right) const {
        return FindMax(0, 0, Size - 1, left - 1, right - 1);
    }

    void Update(uint64_t left, uint64_t right, int64_t delta) {
        Update(0, 0, Size - 1, left - 1, right - 1, delta);
    }

    void Request(uint64_t qnty) {
        for (uint64_t m = 0; m < qnty; ++m) {
            while (isspace(std::cin.peek())) {
                std::cin.get();
            }
            char cmd = std::cin.get();
            switch (cmd) {
                uint64_t left, right;
            case 'm':
                std::cin >> left >> right;
                std::cout << FindMax(left, right) << ' ';
                break;
            case 'a':
                int64_t delta;
                std::cin >> left >> right >> delta;
                Update(left, right, delta);
                break;
            default:
                break;
            }
        }
    }

    std::vector<uint64_t> TreeInput(uint64_t size) const {
        std::vector<uint64_t> source(size);
        for (auto &it : source) {
            std::cin >> it;
        }
        return source;
    }

private:
    void BuildTree(const std::vector<uint64_t> &src, uint64_t index, uint64_t curLeft, uint64_t curRight) {
        if (curLeft == curRight) {
            Tree[index] = {src[curLeft], 0};
        } else {
            uint64_t mid = curLeft + (curRight - curLeft) / 2;
            BuildTree(src, uint64_t(2 * index + 1), curLeft, mid);
            BuildTree(src, uint64_t(2 * index + 2), mid + 1, curRight);
            Tree[index] = std::max(Tree[uint64_t(2 * index + 1)], Tree[uint64_t(2 * index + 2)]);
        }
    }

    uint64_t FindMax(uint64_t index, uint64_t curLeft, uint64_t curRight, uint64_t left, uint64_t right) const {
       if (left > right || index >= 4 * Size) {
            return 0;
        }
        if (curLeft == left && curRight == right) {
            return Tree[index].Value + Tree[index].Delta;
        }
        uint64_t mid = curLeft + (curRight - curLeft) / 2;
        return std::max(FindMax(uint64_t(2 * index + 1), curLeft, mid, left, std::min(right, mid)),
            FindMax(uint64_t(2 * index + 2), mid + 1, curRight, std::max(left, mid + 1), right)) + Tree[index].Delta;
    }

    void Update(uint64_t index, uint64_t curLeft, uint64_t curRight, uint64_t left, uint64_t right, uint64_t delta) {
        if (left > right || index >= 4 * Size) {
            return;
        }
        if (left == curLeft && right == curRight) {
            Tree[index].Delta += delta;
        } else {
            uint64_t mid = curLeft + (curRight - curLeft) / 2;
            Update(uint64_t(2 * index + 1), curLeft, mid, left, std::min(right, mid), delta);
            Update(uint64_t(2 * index + 2), mid + 1, curRight, std::max(left, mid + 1), right, delta);
            uint64_t leftMax = Tree[uint64_t(2 * index + 1)].Value + Tree[uint64_t(2 * index + 1)].Delta;
            uint64_t rightMax = Tree[uint64_t(2 * index + 2)].Value + Tree[uint64_t(2 * index + 2)].Delta;
            Tree[index].Value = std::max(leftMax, rightMax);
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
