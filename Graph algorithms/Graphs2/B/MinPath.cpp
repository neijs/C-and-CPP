#include<iostream>
#include<vector>
#include<cmath>


class TGraph {
    int Cities;
    std::vector<std::pair<int, int>> CityMap;
    std::vector<std::pair<std::pair<int, int>, int>> Special;
public:
    TGraph()
        : Cities(0)
        , CityMap({})
        , Special({})
    {
        std::cin >> Cities;
    }

    void FillGraph() {
        for (int i = 0; i < Cities; ++i) {
            int x, y;
            std::cin >> x >> y;
            std::pair<int, int> City(x, y);
            CityMap.push_back(City);
        }
        int specialQuantity;
        std::cin >> specialQuantity;
        for (int i = 0; i < specialQuantity; ++i) {
            int cityA, cityB, price;
            std::cin >> cityA >> cityB >> price;
            std::pair<int, int> cities(cityA, cityB);
            std::pair<std::pair<int, int>, int> special(cities, price);
            Special.push_back(special);
        }
    }

    void FindMinPath() {
        double maxDistanse = 10e7;
        std::vector<std::pair<bool, double>> finished(Cities);
        for (int i = 0; i < Cities; ++i) {
            finished[i].first = false;
            finished[i].second = (i == 0) ? 0 : maxDistanse;
        }
        // for (int i = 0; i < Cities)
    }
};