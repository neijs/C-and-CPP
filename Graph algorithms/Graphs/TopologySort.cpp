#include <iostream>
#include <vector>
#include <stack>


class TGraph {
    int Vertex, Edge;
    std::vector<std::vector<int>> Graph;
public:
    TGraph()
        : Vertex(0)
        , Edge(0)
        , Graph({})
    {
        std::cin >> Vertex >> Edge;
        Graph.resize(Vertex);
    }

    void FillGraph() {
        for (int i = 0; i < Edge; ++i) {
            int begin, end;
            std::cin >> begin >> end;
            Graph[begin - 1].push_back(end - 1);
        }
    }

    void TopologySort() const {
        std::vector<bool> visited, finished;
        std::stack<int> order;
        visited.assign(Vertex, false);
        finished.assign(Vertex, false);
        for (int i = 0; i < Vertex; ++i) {
            if (Visit(i, visited, finished, order)) {
                std::cout << "No" << std::endl;
                return;
            }
        }
        std::cout << "Yes" << std::endl;
        while (order.empty() == false) {
            std::cout << order.top() + 1 << " ";
            order.pop();
        }
        std::cout << std::endl;
    }
private:
    bool Visit(
        int vertex,
        std::vector<bool>& visited,
        std::vector<bool>& finished,
        std::stack<int>& order
    ) const {
        if (finished[vertex])
            return false;
        if (visited[vertex])
            return true;
        visited[vertex] = true;
        for (int neighb : Graph[vertex]) {
            if (Visit(neighb, visited, finished, order))
                return true;
        }
        finished[vertex] = true;
        order.push(vertex);
        return false;
    }
};

int main() {
    TGraph graph;
    graph.FillGraph();
    graph.TopologySort();
    return 0;
}