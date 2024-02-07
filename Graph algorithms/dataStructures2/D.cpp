#include <iostream>
#include <random>

struct TNode {
    int Key;
    unsigned Priority;
    TNode *Left, *Right;
    static std::mt19937_64 Producer;

    TNode(int key)
        : Key(key)
        , Priority(Producer())
        , Left(nullptr)
        , Right(nullptr)
    {
    }
};

std::mt19937_64 TNode::Producer(rand());

class TTreap {
private:
    TNode *Head;

public:
    TTreap() 
        : Head(nullptr) 
    {}

    int Find(int value) {
        auto pair = Split(Head, value);
        int result = FindMin(pair.second);
        Head = Merge(pair.first, pair.second);
        return result;
    }

    void Insert(int value) {
        auto pair = Split(Head, value);
        Head = Merge(Merge(pair.first, new TNode(value)), pair.second);
    }

    ~TTreap() {
        TreapFlush(Head);
    }

    TTreap(const TTreap&) = delete;

    TTreap& operator=(const TTreap&) = delete;

    void Request(int64_t qnty) {
        for (int64_t i = 0, prev = 0; i < qnty; ++i) {
            while (isspace(std::cin.peek())) {
                std::cin.get();
            }
            char cmd = std::cin.get();
            switch (cmd) {
                int64_t value;
            case '+':
                std::cin >> value;
                Insert((value + prev) % 1000000000);
                prev = 0;
                break;
            case '?':
                std::cin >> value;
                prev = Find(value);
                std::cout << prev << std::endl;
                break;
            default:
                break;
            }
        }
    }

private:
    void TreapFlush(TNode *ptr) {
        if (ptr == nullptr) {
            return;
        }
        TreapFlush(ptr->Left);
        TreapFlush(ptr->Right);
        delete ptr;
    }

    std::pair<TNode*, TNode*> Split(TNode *ptr, int value) {
        if (ptr == nullptr) {
            return {nullptr, nullptr};
        } else if (value > ptr->Key) {
            auto pair = Split(ptr->Right, value);
            ptr->Right = pair.first;
            return {ptr, pair.second};
        } else {
            auto pair = Split(ptr->Left, value);
            ptr->Left = pair.second;
            return {pair.first, ptr};
        }
    }

    TNode* Merge(TNode *leftSubtree, TNode *rightSubtree) {
        if (leftSubtree == nullptr || rightSubtree == nullptr) {
            return leftSubtree == nullptr ? rightSubtree : leftSubtree;
        } else if (leftSubtree->Priority > rightSubtree->Priority) {
            leftSubtree->Right = Merge(leftSubtree->Right, rightSubtree);
            return leftSubtree;
        }
        rightSubtree->Left = Merge(leftSubtree, rightSubtree->Left);
        return rightSubtree;
    }

    int FindMin(TNode *ptr) {
        if (ptr == nullptr) {
            return -1;
        } else if (ptr->Left == nullptr) {
            return ptr->Key;
        }
        return FindMin(ptr->Left);
    }
};

int main() {
    int64_t N;
    std::cin >> N;
    TTreap treap;
    treap.Request(N);
    return 0;
}
