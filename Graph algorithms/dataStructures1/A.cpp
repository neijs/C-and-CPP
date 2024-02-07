#include <iostream>


class TNode {
public:
    int Data;
    TNode *Left, *Right;

    TNode(int value)
        : Data(value)
        , Left(NULL)
        , Right(NULL)
    {}
};

class TBST {
public:
    TNode *Root;

    TBST()
        : Root(NULL)
    {}

    void Insert(int value) {
        Insert(Root, value);
    }

    void Insert(TNode *&tree, int value) {
        if (tree == NULL) {
            tree = new TNode(value);
            return;
        }
        if (tree->Data == value) {
            return;
        }
        if (value < tree->Data) {
            Insert(tree->Left, value);
        } else {
            Insert(tree->Right, value);
        }
    }

    int FindHeight(TNode *tree) {
        if (tree == NULL) {
            return 0;
        }
        int left = FindHeight(tree->Left);
        int right = FindHeight(tree->Right);
        if (left > right) {
            return left + 1;
        } else {
            return right + 1;
        }
    }
};

int main() {
    TBST tree;
    int num;
    while (std::cin >> num && num != 0) {
        tree.Insert(tree.Root, num);
    }
    std::cout << tree.FindHeight(tree.Root) << std::endl; 
    return 0;
}
