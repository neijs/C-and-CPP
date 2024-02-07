#include <iostream>
#include <vector>


class TDSU {
private:
    std::vector<unsigned> Parent, Rank;

public:
    TDSU(unsigned amount);
    unsigned Find(unsigned v) const;
    bool Union(unsigned a, unsigned b);
};

class TGraph {
private:
    unsigned Row, Col, NodeQuantity;
    std::vector<unsigned> RTable;
    TDSU Nodes;

public:
    TGraph(unsigned row, unsigned col) 
        : Row(row)
        , Col(col)
        , NodeQuantity(row * col)
        , RTable()
        , Nodes(NodeQuantity)
    {
    }

    void FillGraph() {
        for (unsigned i = 0; i < NodeQuantity; ++i) {
            unsigned jumper;
            std::cin >> jumper;
            BuildRTable(i, jumper);
            switch (jumper) {
                case 0:
                    break;
                case 1:
                    Nodes.Union(i, i + Col);
                    break;
                case 2:
                    Nodes.Union(i, i + 1);
                    break;
                case 3:
                    Nodes.Union(i, i + Col);
                    Nodes.Union(i, i + 1);
                    break;
                default:
                    break;
            }
        }
    }

    std::pair<unsigned, std::vector<std::pair<unsigned, unsigned>>> BuildMST() {
        unsigned cost = 0;
        std::vector<std::pair<unsigned, unsigned>> addOn;
        for (unsigned i = 0; i < NodeQuantity; ++i) {
            if (RTable[i] % 2 == 1) {
                if (Nodes.Union(i, i + Col)) {
                    cost += 1;
                    addOn.emplace_back(i, 1);
                }
            }
        }
        for (unsigned i = 0; i < NodeQuantity; ++i) {
            if (RTable[i] == 3 || RTable[i] == 2) {
                if (Nodes.Union(i, i + 1)) {
                    cost += 2;
                    addOn.emplace_back(i, 2);
                }
            }
        }
        return std::make_pair(cost, addOn);
    }

private:
    void BuildRTable(unsigned coord, unsigned jumper) {
        if (coord == NodeQuantity - 1) {
            RTable.push_back(jumper);
        } else if (coord % Col == Col - 1) {
            RTable.push_back(abs(jumper - 1));
        } else if (coord >= NodeQuantity - Col) {
            RTable.push_back(abs(jumper - 2));
        } else {
            RTable.push_back(abs(jumper - 3));
        }
    }
};

TDSU::TDSU(unsigned size)
    : Parent(size)
    , Rank(size)
{
    for (unsigned set = 0; set < size; ++set) {
        Parent[set] = set;
        Rank[set] = 0;
    }
}

unsigned TDSU::Find(unsigned v) const {
    if (v == Parent[v]) {
        return v;
    }
    return Find(Parent[v]);
}

bool TDSU::Union(unsigned a, unsigned b) {
    a = Find(a);
    b = Find(b);
    if (a != b) {
        if (Rank[a] < Rank[b]) {
            std::swap(a, b);
        }
        Parent[b] = a;
        if (Rank[a] == Rank[b]) {
            ++Rank[a];
        }
        return true;
    }
    return false;
}

int main() {
    unsigned row, col;
    std::cin >> row >> col;
    TGraph graph(row, col);
    graph.FillGraph();
    auto x = graph.BuildMST();
    std::cout << x.second.size() << " " << x.first << std::endl;
    for (auto jumper : x.second) {
        unsigned i = jumper.first / col + 1;
        unsigned j = jumper.first % col + 1; 
        std::cout << i << " " << j << " " << jumper.second << std::endl;
    }
    return 0;
}