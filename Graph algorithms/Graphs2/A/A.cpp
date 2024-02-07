#include <iostream>
#include <vector>


class TGraph {
    int Vertex;
    std::vector<std::vector<int>> Distants;
public:
    TGraph()
        : Vertex(0)
        , Distants({})
    {
        std::cin >> Vertex;
        Distants.resize(Vertex);
    }

    void FillGraph() {
        for (int i = 0; i < Vertex; ++i) {
            Distants[i].resize(Vertex);
            for (int j = 0; j < Vertex; ++j) {
                std::cin >> Distants[i][j];
            }
        }
    }

    void Floyd() {
        for (int k = 0; k < Vertex; ++k) {
            for (int i = 0; i < Vertex; ++i) {
                for (int j = 0; j < Vertex; ++j) {
                    Distants[i][j] = std::min(Distants[i][j], Distants[i][k] + Distants[k][j]);
                }
            }
        }
    }

    void Print() const {
        for (int i = 0; i < Vertex; ++i) {
            for (int j = 0; j < Vertex; ++j) {
                std::cout << Distants[i][j] << ' ';
            }
            std::cout << std::endl;
        }
    }
};

int main() {
    TGraph graph;
    graph.FillGraph();
    graph.Floyd();
    graph.Print();
    return 0;
}