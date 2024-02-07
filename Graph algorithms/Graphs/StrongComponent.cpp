#include <iostream>
#include <vector>
#include <stack>


class TGraph {
    int Vertex, Edge;
    std::vector<std::vector<int>> Graph, GraphT;
public:
    TGraph() 
    : Vertex(0)
    , Edge(0)
    , Graph({})
    , GraphT({})
    {
        std::cin >> Vertex >> Edge;
        Graph.resize(Vertex);
        GraphT.resize(Vertex);
    }

    void FillGraph() {
        for (int i = 0; i < Edge; ++i) {
            int begin, end;
            std::cin >> begin >> end;
            Graph[begin - 1].push_back(end - 1);
            GraphT[end - 1].push_back(begin - 1);
        }
    }

    void KosarajusAlgo() const {
        int compNum = 0;
        std::vector<bool> visited;
        std::vector<int> assigned;
        std::stack<int> L;
        visited.assign(Vertex, false);
        assigned.assign(Vertex, 0);
        for (int i = 0; i < Vertex; ++i) {
            Visit(i, visited, L);
        }
        while (L.empty() == false) {
            int vertex = L.top();
            L.pop();
            if (assigned[vertex] == 0) {
                ++compNum;
                AssignComp(vertex, assigned, compNum);
            }
        }
        std::cout << compNum << std::endl;
        for (auto comp : assigned) {
            std::cout << comp << " ";
        }
        std::cout << std::endl;
    }
private:
    void Visit(int vertex, std::vector<bool>& visited, std::stack<int>& L) const {
        if (visited[vertex] == true)
            return;
        visited[vertex] = true;
        for (auto outNeighb : Graph[vertex]) {
            if (visited[outNeighb] == false)
                Visit(outNeighb, visited, L);
        }
        L.push(vertex);
    }

    void AssignComp(int vertex, std::vector<int>& assigned, int compNum) const {
        if (assigned[vertex] != 0)
            return;
        assigned[vertex] = compNum;
        for (auto inNeighb : GraphT[vertex]) {
            AssignComp(inNeighb, assigned, compNum);
        }
    }
};

int main() {
    TGraph graph;
    graph.FillGraph();
    graph.KosarajusAlgo();
    return 0;
}