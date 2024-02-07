#include <iostream>
#include <vector>
#include <string>

struct TRequest {
    int To;
    int Number;
};

class TTarjan {
private:
    size_t Quantity;
    std::vector<std::vector<int>> Graph;
    std::vector<bool> Visited;
    std::vector<int> LCA;
    std::vector<int> Parents;

    int FindDSU(int v) {
        if (v == LCA[v]) {
            return v;
        } else {
            LCA[v] = FindDSU(LCA[v]);
            return LCA[v];
        }
    }

    void UnionDSU(int v, int u, int p) {
        v = FindDSU(v);
        u = FindDSU(u);
        LCA[v] = u;
        Parents[u] = p;
    }

    void DFS(std::vector<std::vector<TRequest>> &requests
            , std::vector<int> &answer
            , int v)
    {
        Visited[v] = true;
        LCA[v] = v;
        Parents[v] = v;
        for (size_t i = 0; i < Graph[v].size(); ++i) {
            if (!Visited[Graph[v][i]]) {
                DFS(requests, answer, Graph[v][i]);
                UnionDSU(v, Graph[v][i], v);
            }
        }
        for (size_t i = 0; i < requests[v].size(); ++i) {
            if (Visited[requests[v][i].To]) {
                answer[requests[v][i].Number] = Parents[FindDSU(requests[v][i].To)];
            }
        }
    }
public:
    TTarjan() : Quantity(1), Graph({}), Visited({}), LCA({}), Parents({}) {}

    void Add(std::vector<std::pair<int, int>> &newNodes) {
        Quantity += newNodes.size();
        Graph.resize(Quantity);
        Visited.resize(Quantity);
        LCA.resize(Quantity);
        Parents.resize(Quantity);
        for (size_t i = 0; i < newNodes.size(); ++i) {
            Graph[newNodes[i].first].push_back(newNodes[i].second);
        }
    }

    std::vector<int> Requests(int num, std::vector<std::vector<TRequest>> &requests) {
        std::vector<int> answer(num);
        DFS(requests, answer, 0);
        return answer;
    }

    void InitTarjan(int count, int &number, int size, std::vector<std::vector<TRequest>> &requests) {
        std::vector<std::pair<int, int>> newNodes;
        for (int i = 0; i < count; ++i) {
            std::string str;
            int a, b;
            std::cin >> str >> a >> b;
            if (str == "ADD") {
                newNodes.push_back({a - 1, b - 1});
                ++size;
            } else if (str == "GET") {
                requests.resize(size);
                requests[a - 1].push_back({b - 1, number});
                requests[b - 1].push_back({a - 1, number});
                ++number;
            }
        }
        Add(newNodes);
    }

    void MainRequest(std::vector<std::vector<TRequest>> &requests, int number) {
        if (!requests.empty()) {
            std::vector<int> parents = Requests(number, requests);
            for (size_t i = 0; i < parents.size(); ++i) {
                std::cout << parents[i] + 1 << std::endl;
            }
        }
    }
};

int main() {
    int count, number = 0, size = 1;
    std::cin >> count;
    std::vector<std::vector<TRequest>> requests(size);
    TTarjan object;
    object.InitTarjan(count, number, size, requests);
    object.MainRequest(requests, number);
    return 0;
}