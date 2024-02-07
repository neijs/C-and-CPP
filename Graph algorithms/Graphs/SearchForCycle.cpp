#include <iostream>
#include <vector>


class TGraph {
    int Vertex;
    std::vector<std::vector<int>> Graph;
public:
    TGraph()
        : Vertex(0)
        , Graph({})
    {
        std::cin >> Vertex;
        Graph.resize(Vertex);
    }

    void FillGraph() {
        for (int i = 0; i < Vertex; ++i) {
            for (int j = 0; j < Vertex; ++j) {
                int edge;
                std::cin >> edge;
                if (edge == 1)
                    Graph[i].push_back(j);
            }
        }
    }

    void HasCycle() const {
        std::vector<bool> visited, finished;
        visited.assign(Vertex, false);
        finished.assign(Vertex, false);
        for (int i = 0; i < Vertex; ++i) {
            if (DepthFirstSearch(i, visited, finished)) {
                std::cout << 1 << std::endl;
                return;
            }
        }
        std::cout << 0 << std::endl;
    }
private:
    bool DepthFirstSearch(
        int vertex, 
        std::vector<bool>& visited, 
        std::vector<bool>& finished
    ) const {
        if (finished[vertex])
            return false;
        if (visited[vertex])
            return true;
        visited[vertex] = true;
        for (int neighb : Graph[vertex]) {
            if (DepthFirstSearch(neighb, visited, finished))
                return true;
        }
        finished[vertex] = true;
        return false;
    }
};

int main() {
    TGraph graph;
    graph.FillGraph();
    graph.HasCycle();
    return 0;
}