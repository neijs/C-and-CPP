#include <iostream>
#include <vector>


class TDisjointSetUnion {
private:
    mutable std::vector<unsigned> Parent;
    std::vector<unsigned> Rank;
    unsigned SetsAmount;

public:
    TDisjointSetUnion(unsigned amount)
        : Parent(amount)
        , Rank(amount)
        , SetsAmount(amount)
    {
        for (unsigned set = 0; set < SetsAmount; ++set) {
            Parent[set] = set;
            Rank[set] = 0;
        }
    }

    unsigned FindSet(unsigned set) const {
        if (Parent[set] == set) {
            return set;
        }
        return Parent[set] = FindSet(Parent[set]);
    }

    void UnionSet(unsigned x, unsigned y) {
        x = FindSet(x);
        y = FindSet(y);
        if (x != y) {
            if (Rank[x] < Rank[y]) {
                std::swap(x, y);
            }
            Parent[y] = x;
            if (Rank[x] == Rank[y]) {
                ++Rank[x];
            }
            --SetsAmount;
        }
    }

    bool Unified() const {
        return SetsAmount == 1;
    }
};

int main() {
    unsigned amount;
    std::cin >> amount;
    TDisjointSetUnion dsu(amount);
    unsigned M;
    std::cin >> M;
    unsigned count = 0;
    for (count = 0; count < M && !dsu.Unified(); ++count) {
        unsigned first, second;
        std::cin >> first >> second;
        dsu.UnionSet(first, second);
    }
    std::cout << count << std::endl;
    return 0;
}