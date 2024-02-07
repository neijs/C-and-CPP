#include <iostream>
#include <string>
char c;

void gc() { c = std::cin.get(); }

int main() {
    enum state {H, A, B, S, ER};
    state CS = H;
    std::string chain = "";
    do {
        gc();
        chain += c;
        switch (CS) {
            case H:
                if (c == 'a') CS = A;
                else CS = ER;
                break;
            case A:
                if (c == 'a') CS = B;
                else if (c != 'd') CS = ER;
                break;
            case B:
                if (c == 'a') CS = A;
                else if (c == '\n') CS = S;
                else CS = ER;
                break;
            default:
                break;
        }
    } while (CS != S && CS != ER);
    if (CS == S) std::cout << chain;
    else std::cerr << "Error in Lexcem: " << c << std::endl;
    return 0;
}