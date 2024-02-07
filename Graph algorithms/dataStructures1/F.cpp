#include<iostream>
#include<vector>


int levenshtein(std::string s1, std::string s2) {
    if (s1.length() > s2.length()) {
        std::swap(s1, s2);
        //std::swap(s1.length(), s2.length());
    }
    std::vector<int> current(s1.length() + 1);
    for (size_t i = 0; i <= s1.length(); ++i) {
        current[i] = i;
    }
    for (size_t i = 1; i <= s2.length(); ++i) {
        std::vector<int> previous(s1.length() + 1);
        previous = current;
        current[0] = i;
        for (size_t j = 1; j <= s1.length(); ++j) {
            current[j] = j;
        }
        for (size_t j = 1; j <= s1.length(); ++j) {
            int add = previous[j] + 1;
            int erase = current[j - 1] + 1;
            int change = previous[j - 1];
            if (s1[j - 1] != s2[i - 1]) {
                change += 1;
            }
            current[j] = std::min(std::min(add, erase), change);
        }
    }
    return current[s1.length()];
}

int main() {
    std::string s1, s2;
    std::cin >> s1 >> s2;
    std::cout << levenshtein(s1, s2) << std::endl;
}