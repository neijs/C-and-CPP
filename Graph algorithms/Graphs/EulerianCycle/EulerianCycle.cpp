#include <iostream>
#include <vector>
#include <stack>

class TGraph {
    int Vertex, Routes, Start, NotIsolVertecies;
    std::vector <std::vector <int>> Graph, GraphT;
public:
    TGraph() : Vertex(0), Routes(0), Start(0), NotIsolVertecies(0), Graph({}), GraphT({}) {
        std::cin >> Routes >> Vertex;
        Graph.resize(Vertex);
        GraphT.resize(Vertex);
        for (int i = 0; i < Routes; ++i) {
            int stops;
            std::cin >> stops;
            int buf[2] = {0, 0};
            for (int j = 0; j < stops; ++j) {
                if (j == 0) {
                    std::cin >> buf[0] >> buf[1];
                } else {
                    buf[0] = buf[1];
                    std::cin >> buf[1];
                }
                Start = buf[0];
                if (Graph[buf[0] - 1].size() == 0) {
                    ++NotIsolVertecies;
                }
                Graph[buf[0] - 1].push_back(buf[1]);
                GraphT[buf[1] - 1].push_back(buf[0]);
            }
        }
    }

    void FindEulCycle() {
        if (!EulCycleExist()) {
            std::cout << 0 << std::endl;
            return;
        }

        std::stack <int> stack;
        std::vector<int> eulCycle;

        stack.push(Start);
        while (!stack.empty()) {
            int u = stack.top();
            int w = FindUnmarkedEdge(u);
            if (w != -1) {
                stack.push(w);
            } else {
                stack.pop();
                eulCycle.push_back(u);
            }
        }    
        std::cout << eulCycle.size() << " ";
        for (ssize_t i = eulCycle.size() - 1; i >= 0; --i) {
            std::cout << eulCycle[i] << " ";
        }
        std::cout << std::endl;   
    }
private:
    bool EulCycleExist() const {
        std::vector <bool> used;
        used.assign(Vertex, false);
        int unic = 0;
        Dfs1(Start - 1, used, unic);
        return (NotIsolVertecies == unic) ? true : false;
    }

    int FindUnmarkedEdge(int vertex) {
        if (Graph[vertex - 1].size() == 0) {
            return -1;
        } else {
            int w = Graph[vertex - 1].front();
            for (size_t i = 0; i < Graph[vertex - 1].size(); ++i) {
                if (i == Graph[vertex - 1].size() - 1) {
                    Graph[vertex - 1].pop_back();
                } else {
                    Graph[vertex - 1][i] = Graph[vertex - 1][i + 1];
                }
            }
            return w;
        }
    }

    void Dfs1(int vertex, std::vector<bool>& used, int& unic) const {
        unic++;
        used[vertex] = true;
        for (size_t i = 0; i < Graph[vertex].size(); ++i) {
            if (!used[Graph[vertex][i] - 1]) {
                Dfs1(Graph[vertex][i] - 1, used, unic);
            }
        }
    }
};

int main() {
    TGraph graph;

    graph.FindEulCycle();
    return 0;
}