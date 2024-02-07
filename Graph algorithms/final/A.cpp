#include <iostream>
#include <vector>

int FindMax(std::vector<size_t> &weights, std::vector<size_t> &costs, size_t quantity, size_t threshold) {
    std::vector<std::vector<size_t>> DinamicMatrix(quantity + 1);
    for (std::vector<size_t> &elements : DinamicMatrix) {
        elements.resize(threshold + 1);
    }
    for (size_t i = 1; i <= quantity; ++i) {
        for (size_t j = 0; j <= threshold; ++j) {
            DinamicMatrix[i][j] = DinamicMatrix[i - 1][j];
            if (j >= weights[i] && DinamicMatrix[i - 1][j - weights[i]] + costs[i] > DinamicMatrix[i][j]) {
                DinamicMatrix[i][j] = DinamicMatrix[i - 1][j - weights[i]] + costs[i];
            }
        }
    }
    return DinamicMatrix[quantity][threshold];
}

void Request(size_t quantity, size_t threshold) {
    std::vector<size_t> weights(quantity + 1), costs(quantity + 1);
    for (size_t i = 1; i <= quantity; ++i) {
        std::cin >> weights[i];
    }
    for (size_t i = 1; i <= quantity; ++i) {
        std::cin >> costs[i];
    }
    std::cout << FindMax(weights, costs, quantity, threshold) << std::endl;
}

int main() {
    size_t N, M;
    std::cin >> N >> M;
    Request(N, M);
    return 0;
}
