#include <iostream>
#include <vector>

char c;

void gc() { c = std::cin.get(); }

int main() {
    std::vector<int> number;
    enum state { H, DT1, DT2, DT3, DT4, DT5, 
    DH1, DH2, DH3, DH4, DH5, DT1DH1, DT1DH2,
    DT1DH3, DT1DH4, DT2DH1, DT2DH2, DT2DH3,
    DT3DH1, DT3DH2, DT4DH1, DH1DT1, DH1DT2,
    DH1DT3, DH1DT4, DH2DT1, DH2DT2, DH2DT3,
    DH3DT1, DH3DT2, DH4DT1, S, ER };
    state CS = H;
    do {
        gc();
        switch (CS) {
            case H:
                if (c == '.') CS = DT1;
                else if (c == '-') CS = DH1;
                else CS = ER;
                break;
            case DT1:
                if (c == '.') CS = DT2;
                else if (c == '-') CS = DT1DH1;
                else CS = ER;
                break;
            case DT2:
                if (c == '.') CS = DT3;
                else if (c == '-') CS = DT2DH1;
                else CS = ER;
                break;
            case DT3:
                if (c == '.') CS = DT4;
                else if (c == '-') CS = DT3DH1;
                else CS = ER;
                break;
            case DT4:
                if (c == '.') CS = DT5;
                else if (c == '-') CS = DT4DH1;
                else CS = ER;
                break;
            case DT5:
                if (c != ' ' && c != '\n') { CS = ER; break; }
                CS = (c == ' ') ? H : S;
                number.push_back(5);
                break;
            case DH1:
                if (c == '.') CS = DH1DT1;
                else if (c == '-') CS = DH2;
                else CS = ER;
                break;
            case DH2:
                if (c == '.') CS = DH2DT1;
                else if (c == '-') CS = DH3;
                else CS = ER;
                break;
            case DH3:
                if (c == '.') CS = DH3DT1;
                else if (c == '-') CS = DH4;
                else CS = ER;
                break;
            case DH4:
                if (c == '.') CS = DH4DT1;
                else if (c == '-') CS = DH5;
                else CS = ER;
                break;
            case DH5:
                if (c != ' ' && c != '\n') { CS = ER; break; }
                CS = (c == ' ') ? H : S;
                number.push_back(0);
                break;
            case DT1DH1:
                if (c != '-') { CS = ER; break; }
                CS = DT1DH2;
                break;
            case DT1DH2:
                if (c != '-') { CS = ER; break; }
                CS = DT1DH3;
                break;
            case DT1DH3:
                if (c != '-') { CS = ER; break; }
                CS = DT1DH4;
                break;
            case DT1DH4:
                if (c != ' ' && c != '\n') { CS = ER; break; }
                CS = (c == ' ') ? H : S;
                number.push_back(1);
                break;
            case DT2DH1:
                if (c != '-') { CS = ER; break; }
                CS = DT2DH2;
                break;
            case DT2DH2:
                if (c != '-') { CS = ER; break; }
                CS = DT2DH3;
                break;
            case DT2DH3:
                if (c != ' ' && c != '\n') { CS = ER; break; }
                CS = (c == ' ') ? H : S;
                number.push_back(2);
                break;
            case DT3DH1:
                if (c != '-') { CS = ER; break; }
                CS = DT3DH2;
                break;
            case DT3DH2:
                if (c != ' ' && c != '\n') { CS = ER; break; }
                CS = (c == ' ') ? H : S;
                number.push_back(3);
                break;
            case DT4DH1:
                if (c != ' ' && c != '\n') { CS = ER; break; }
                CS = (c == ' ') ? H : S;
                number.push_back(4);
                break;
            case DH1DT1:
                if (c != '.') { CS = ER; break; }
                CS = DH1DT2;
                break;
            case DH1DT2:
                if (c != '.') { CS = ER; break; }
                CS = DH1DT3;
                break;
            case DH1DT3:
                if (c != '.') { CS = ER; break; }
                CS = DH1DT4;
                break;
            case DH1DT4:
                if (c != ' ' && c != '\n') { CS = ER; break; }
                CS = (c == ' ') ? H : S;
                number.push_back(6);
                break;
            case DH2DT1:
                if (c != '.') { CS = ER; break; }
                CS = DH2DT2;
                break;
            case DH2DT2:
                if (c != '.') { CS = ER; break; }
                CS = DH2DT3;
                break;
            case DH2DT3:
                if (c != ' ' && c != '\n') { CS = ER; break; }
                CS = (c == ' ') ? H : S;
                number.push_back(7);
                break;
            case DH3DT1:
                if (c != '.') { CS = ER; break; }
                CS = DH3DT2;
                break;
            case DH3DT2:
                if (c != ' ' && c != '\n') { CS = ER; break; }
                CS = (c == ' ') ? H : S;
                number.push_back(8);
                break;
            case DH4DT1:
                if (c != ' ' && c != '\n') { CS = ER; break; }
                CS = (c == ' ') ? H : S;
                number.push_back(9);
                break;
            default:
                break;
        }
    } while (CS != S && CS != ER);
    if (CS == S) {
        for (auto elem : number) 
            std::cout << elem;
        std::cout << std::endl;
    } else std::cerr << "Error in Lexeme: " << c << std::endl;
    return 0;
}