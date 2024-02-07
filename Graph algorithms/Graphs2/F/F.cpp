#include<iostream>
#include<vector>
#include<queue>
#include<climits>


class TGraph {
private:
    int Towns, Roads;
    std::vector<std::vector<std::pair<int, int>>> Graph;
public:
    TGraph(int towns, int roads)
        : Towns(towns)
        , Roads(roads)
        , Graph()
    {
        Graph.resize(Towns);
    }

    void FillGraph() {
        for (int i = 0; i < Roads; ++i) {
            int from, to, len;
            std::cin >> from >> to >> len;
            Graph[from - 1].push_back(std::make_pair(len, to - 1));
            Graph[to - 1].push_back(std::make_pair(len, from - 1));
        }
    }

    long long FindMinPath(int start, int finish) const {
        const long long inf = LLONG_MAX;
        std::vector<long long> dist(Towns, inf);
        dist[start - 1] = 0;
        std::priority_queue<std::pair<long long, int>> q;
        q.push(std::make_pair(0, start - 1));
        while (!q.empty()) {
            long long curDist = -q.top().first;
            int town = q.top().second;
            q.pop();
            if (curDist > dist[town]) {
                continue;
            }
            for (size_t i = 0; i < Graph[town].size(); ++i) {
                long long len = Graph[town][i].first;
                int to = Graph[town][i].second;
                if (dist[town] + len < dist[to]) {
                    dist[to] = dist[town] + len;
                    q.push(std::make_pair(-dist[to], to));
                }
            }
        }
        return (dist[finish - 1] == inf) ? -1 : dist[finish - 1];
    }
};

int main() {
    int towns, roads;
    std::cin >> towns >> roads;
    TGraph graph(towns, roads);
    graph.FillGraph();
    int start, finish;
    std::cin >> start >> finish;
    std::cout << graph.FindMinPath(start, finish) << std::endl;
    return 0;
}