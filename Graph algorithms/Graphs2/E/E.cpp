#include <iostream>
#include <deque>
#include <vector>
#include <climits>


class TGraph {
    int Vertex;
    std::vector<std::vector<std::pair<int, int>>> Graph;
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
            int from, to, price;
            std::cin >> from >> to >> price;
            Graph[from - 1].push_back(std::make_pair(to - 1, price));
            Graph[to - 1].push_back(std::make_pair(from - 1, price));
        }
    }

    std::vector<int> BFS() const {
        std::vector<int> dist(Vertex, INT32_MAX); 
        std::deque<int> deq;
        deq.push_back(0);
        dist[0] = 0;
        while (!deq.empty()) {
            int vertex = deq.front();
            deq.pop_front();
            for (size_t i = 0; i < Graph[vertex].size(); ++i) {
                if (dist[Graph[vertex][i].first] > dist[vertex] + Graph[vertex][i].second) {
                    dist[Graph[vertex][i].first] = dist[vertex] + Graph[vertex][i].second;
                    if (Graph[vertex][i].second == 0) {
                        deq.push_front(Graph[vertex][i].first);
                    } else {
                        deq.push_back(Graph[vertex][i].first);
                    }
                }
            }
        }
        return dist;
    }
};

int main() {
    TGraph graph;
    graph.FillGraph();
    std::vector<int> dist = graph.BFS();
    for (int vertex : dist) {
        std::cout << vertex << " ";
    }
    std::cout << std::endl;
    return 0;
}
