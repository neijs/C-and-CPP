#include <iostream>
#include <vector>


class TGraph {
    int Vertex;
    int FirstVertex;
    std::vector<std::vector<int>> Graph;
    std::vector<bool> Used;
    std::vector<int> Component;
    void DepthFirstSearch(int numberOfVertex);
public:
    TGraph() : Vertex(0), FirstVertex(0), Graph({}), Used({}), Component({}) {}
    std::istream& ReadFromStream(std::istream& stream);
    void GetConnectedComponent();
};

std::istream& TGraph::ReadFromStream(std::istream& stream) {
    Used.clear();
    Graph.clear();
    Component.clear();
    int m = 0;
    std::vector<int> tmp;
    stream >> Vertex;
    stream >> FirstVertex;
    FirstVertex--;
    for (int i = 0; i < Vertex; ++i) {
        Used.push_back(false);
        for (int j = 0; j < Vertex; ++j) {
            stream >> m;
            if (m)
                tmp.push_back(j);
        }
        Graph.push_back(tmp);
        tmp.clear();
    }
    return stream;
}

void TGraph::DepthFirstSearch(int numberOfVertex) {
    Used[numberOfVertex] = true;
    Component.push_back(numberOfVertex);
    for (size_t i = 0; i < Graph[numberOfVertex].size(); ++i) {
        int to = Graph[numberOfVertex][i];
        if (!Used[to])
            this->DepthFirstSearch(to);
    }
}

void TGraph::GetConnectedComponent() {
    DepthFirstSearch(FirstVertex);
    std::cout << Component.size() << std::endl;
}

int main() {
    TGraph graph;
    graph.ReadFromStream(std::cin);
    graph.GetConnectedComponent();
    return 0;
}