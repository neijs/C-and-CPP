#include <iostream>
#include <vector>
#include <cmath>
#include <limits>

#define EPSILON 10e-5

struct CityStruct {
public:
    int First;
    int Second;
};

class TGraph {
private:
    int Vertex;
    std::vector<CityStruct> Cities;
    std::vector<std::vector<double>> Distants;
    int Start;
    int Finish;

public: 
    TGraph()
    : Vertex(0)
    , Cities()
    , Distants()
    , Start(0)
    , Finish(0)
    {
        std::cin >> Vertex;
        Cities.resize(Vertex);
        Distants.resize(Vertex - 1);
        for (int i = 0; i < Vertex - 1; ++i) {
            std::cin >> Cities[i].First >> Cities[i].Second;
            Distants[i].resize(Vertex - i - 1, -1);
        }
        std::cin >> Cities[Vertex - 1].First >> Cities[Vertex - 1].Second;
        int amountSpecials;
        std::cin >> amountSpecials;
        for (int j = 0; j < amountSpecials; ++j) {
            int a, b;
            std::cin >> a >> b;
            if (b < a)
                std::swap(a, b);
            if (a != b) {
                std::cin >> Distants[a - 1][b - a - 1];
            } else {
                std::cin >> a;
            } 
        }
        for (int i = 0; i < Vertex - 1; ++i) {
            for (int j = 0; j < Vertex - i - 1; ++j) {
                if (Distants[i][j] + 1 < EPSILON) {
                    double first = pow(Cities[i].First - Cities[j + i + 1].First, 2);
                    double second = pow(Cities[i].Second - Cities[j + 1 + i].Second, 2);
                    Distants[i][j] = sqrt(first + second);
                }
            }
        }
        std::cin >> Start >> Finish;
        Start--; 
        Finish--;
        if (Finish < Start)
            std::swap(Start, Finish);
    }

    double Dijkstra() {
        if (Start == Finish)
            return 0;
        std::vector<bool> used;
        std::vector<double> distantsFromStart;
        for (int i = 0; i < Vertex; ++i) {
            distantsFromStart.push_back(10e7);
            used.push_back(false);
        }
        distantsFromStart[Start] = 0;
        for (int i = 0; i < Vertex; ++i) {
            int v = -1;
            for (int j = 0; j < Vertex; ++j) {
                if (!used[j] && (v == -1 || distantsFromStart[j] < distantsFromStart[v]))
                    v = j;
            }
            if (fabs(distantsFromStart[v] - 10e7) < EPSILON)
                break;
            used[v] = true;
            for (int j = 0; j < Vertex; ++j) {
                double tmp = distantsFromStart[v];
                if (v != j) {
                    tmp = distantsFromStart[v] + Distants[std::min(v, j)][abs(v - j) - 1];
                }
                if (tmp < distantsFromStart[j])
                    distantsFromStart[j] = tmp;
            }
        }
        return distantsFromStart[Finish];
    }

};

int main() {
    TGraph graph;
    std::cout << graph.Dijkstra() << std::endl;
    return 0;
}