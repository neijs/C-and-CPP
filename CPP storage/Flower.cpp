#include <iostream>
#include <cstring>
using namespace std;
class Flower {
    char _colour[6];
    unsigned _petals;
    static unsigned _white;
    static unsigned _pink;
public:
    Flower(unsigned petals = 10);
    Flower(const char* colour, unsigned petals = 10);
    ~Flower() {
        (strcmp(_colour, "white") == 0) ? --_white : --_pink;
    }
    void Volshebstvo();
    static void Print_flowers() {
        cout << "White: " << Flower::_white << " Pink: " << Flower::_pink << endl;
    }
};

unsigned Flower::_white = 0;
unsigned Flower::_pink = 0;

Flower::Flower(unsigned petals) {
    _petals = petals;
    Volshebstvo();
}

Flower::Flower(const char* colour, unsigned petals) {
    _petals = petals;
    if (strcmp(colour, "white") != 0 && strcmp(colour,"pink") != 0) Volshebstvo();
    else {
        strcpy(_colour, colour);
        (strcmp(colour,"white") == 0) ? ++_white : ++_pink;
    }
}

void Flower::Volshebstvo() {
    if ((_pink > _white) || ((_pink == _white) && (_petals % 2 == 1))) {
        strcpy(_colour, "white");
        ++_white;
    } else {
        strcpy(_colour, "pink");
        ++_pink;
    }
}