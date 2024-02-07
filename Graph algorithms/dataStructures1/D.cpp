#include <iostream>
#include <vector>
#include <cmath>


class THashTable {
private:
    int p[10];
    size_t HashSize;
    std::vector<int> Table;

public:
    THashTable(size_t hashSize);
    int HashFunction(std::string value) const;
    bool SearchTable(std::string value) const;
    void InsertItem(std::string value);
    void RemoveItem(std::string value);
};


THashTable::THashTable(size_t hashSize)
    : HashSize(hashSize)
    , Table(hashSize)
{
    Table.assign(hashSize, 0);
    for (int i = 0; i < 10; ++i) {
        p[i] = int(pow(29, i));
    }
}

int THashTable::HashFunction(std::string value) const {
    int hashValue = 0;
    for (size_t i = 0; i < value.length(); ++i) {
        hashValue = (hashValue + value[i] * (p[i] % HashSize)) % HashSize;
    }
    return hashValue;
}

bool THashTable::SearchTable(std::string value) const {
    int key = HashFunction(value);
    if (Table[key] == 0) {
        return false;
    }
    return true;
}

void THashTable::InsertItem(std::string value) {
    int key = HashFunction(value);
    if (Table[key] == 0) {
        Table[key] = 1;
    }
    return;
}

void THashTable::RemoveItem(std::string value) {
    int key = HashFunction(value);
    if (Table[key] == 0) {
        return;
    }
    Table[key] = 0;
    return;   
}

int main() {
    const size_t hashSize = 1e6;
    THashTable HT(hashSize);
    char cmd;
    std::string word;
    std::vector<std::string> response;
    while (std::cin >> cmd) {
        if (cmd == '#') {
            for (auto str : response) {
                std::cout << str << std::endl;
            }
            return 0;
        }
        std::cin >> word;
        switch(cmd) {
            case '+':
                HT.InsertItem(word);
                break;
            case '-':
                HT.RemoveItem(word);
                break;
            case '?':
                if (HT.SearchTable(word)) {
                    response.push_back("YES");
                } else {
                    response.push_back("NO");
                }
                break;
            default:
                return 1;
        }
    }
}