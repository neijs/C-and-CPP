#include <iostream>
#include <unistd.h>

void clearScreen(int n, int m);

class Square {
    bool _white, _black, _recent;
public:
    Square(bool white = false, bool black = false, bool recent = false) {
        _white  = white;
        _black  = black;
        _recent = recent;
    }
    void lightup_white() { _white = true;   }
    void turnoff_white() { _white = false;  }
    void lightup_black() { _black = true;   } 
    void turnoff_black() { _black = false;  }
    void renew()         { _recent = true;  }
    void makeold()       { _recent = false; }

    bool white()  const { return _white;           } 
    bool black()  const { return _black;           }
    bool recent() const { return _recent;          }
    bool onfire() const { return _white && _black; }
};

int main() {
    int N, M;
    useconds_t usec = 100000;
    std::cin >> N >> M;

    Square** board = new Square*[N];
    for (int i = 0; i < N; ++i)
        board[i] = new Square[M];

    int white_x, white_y;
    std::cin >> white_x >> white_y;
    board[white_x - 1][white_y - 1].lightup_white();

    int black_x, black_y;
    std::cin >> black_x >> black_y;
    board[black_x - 1][black_y - 1].lightup_black();

    std::cout << "\033c";
    
    int move = 1;
    bool won = false;

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            if (board[i][j].white()) std::cout << "W ";
            else if (board[i][j].black()) std::cout << "B ";
            else std::cout << ". ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
    int a[8] = {2, 1, -1, -2, -2, -1,  1,  2};
    int b[8] = {1, 2,  2,  1, -1, -2, -2, -1};
    while (move != M*N) {
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                bool whites = (move % 2 == 1) && board[i][j].white();
                bool blacks = (move % 2 == 0) && board[i][j].black();
                if ( ( whites || blacks ) && !board[i][j].recent() ) {
                    for (int k = 0; k < 8; ++k) {
                        int newi = i + a[k];
                        int newj = j + b[k];
                        if (newi >= 0 && newi < N && newj >= 0 && newj < M) {
                            if (whites) {
                                board[newi][newj].lightup_white();
                                board[newi][newj].renew();
                            } else if (blacks) {
                                board[newi][newj].lightup_black();
                                board[newi][newj].renew();
                            }
                            if (board[newi][newj].onfire()) won = true;
                        }
                    }
                    if (whites) {
                        board[i][j].turnoff_white();
                        board[i][j].makeold();
                    } else if (blacks) {
                        board[i][j].turnoff_black();
                        board[i][j].makeold();
                    }
                }
            }
        }
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j)
                board[i][j].makeold();
        }
        std::cout << "\033c";
        usleep(usec);
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                if (board[i][j].onfire()) std::cout << "@ ";
                else if (board[i][j].white()) std::cout << "W ";
                else if (board[i][j].black()) std::cout << "B ";
                else std::cout << ". ";
            }
            std::cout << std::endl;
        }    
        usleep(usec);
        if ( !won ) std::cout << "\033c";

        if ( won ) {
            for (int i = 0; i < N; ++i)
                delete [] board[i];
            delete [] board;
            std::cout << move << std::endl;
            return 0;
        }
        ++move;
    }
    for (int i = 0; i < N; ++i)
        delete [] board[i];
    delete [] board;
    std::cout << -1 << std::endl;
    return 0;
}

void clearScreen(int n, int m) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j)
            std::cout << "\b";
    }
}