#define REQLEN 8
#include <iostream>
#include <cstring>

struct square {
    int _col, _row;
    square(int col = 0, int row = 0);
    bool operator==(const square& other) const;
};

class Figure {
protected:
    square _pos;
public:
    virtual ~Figure() {};
    virtual bool move(square target) const = 0;
    void place(square pos);
    bool on_board(square pos) const;
};

struct King : Figure {
    virtual ~King() {};
    bool move(square target) const override;
};

struct Queen : Figure {    
    virtual ~Queen() {};
    bool move(square target) const override;
};

struct Rook : Figure {  
    virtual ~Rook() {};
    bool move(square target) const override;
};

struct Bishop : Figure {  
    virtual ~Bishop() {};
    bool move(square target) const override;
};

struct Knight : Figure {  
    virtual ~Knight() {};
    bool move(square target) const override;
};

class Parser {
    char _req[REQLEN];
    static char const* figures;
    static char const* columns;
public:
    Parser(const char* src);
    int get_piece() const;
    square get_sqr(int i, int j) const;
private:
    int l2i(char c) const;
};

class ChessChecker {
    Figure* _pieces[5];
    char _request[REQLEN];
    int _piece;
    square _start, _target;
public:
    ChessChecker() {
        _pieces[0] = new King;
        _pieces[1] = new Queen;
        _pieces[2] = new Rook;
        _pieces[3] = new Bishop;
        _pieces[4] = new Knight;
    }
    
    ~ChessChecker() {
        for (int i = 0; i < 5; ++i)
            delete _pieces[i];
    }

    void get_req() {
        char c;
        for (int i = 0; (c = std::cin.get()) != '\n' && c != EOF; ++i) {
            if (i == 8) throw "NO";
            _request[i] = c;
        }
        Parser prs(_request);
        _piece = prs.get_piece();
        _start = prs.get_sqr(2, 3);
        _target = prs.get_sqr(5, 6);
    }

    void check_req() {
        _pieces[_piece]->Figure::place(_start);
        if (_pieces[_piece]->move(_target))
            std::cout << "YES" << std::endl;
        else
            std::cout << "NO" << std::endl;
    }
};

char const* Parser::figures = "KQRBN";
char const* Parser::columns = "abcdefgh";

Parser::Parser(const char* src) {
    std::memcpy(_req, src, REQLEN);
}

int Parser::get_piece() const { // "KQRBN" -> "01234"
    char const* pos = std::strchr(figures, _req[0]);
    if (pos == nullptr) throw "NO";
    return pos - figures;
}

square Parser::get_sqr(int i, int j) const {
    return square(l2i(_req[i]), _req[j] - '0');
}

int Parser::l2i(char const c) const { // "abcdefgh" -> "12345678"
    char const* pos = std::strchr(columns, c);
    if (pos == nullptr) throw "NO";
    return 1 + pos - columns;
}

square::square(int col, int row) : _col(col), _row(row) {}

bool square::operator==(const square& other) const {
    return (_col == other._col) && (_row == other._row);
}

void Figure::place(square pos) { 
    if (!on_board(pos)) throw "NO";
    _pos = pos;     
}

bool Figure::on_board(square pos) const {
    return (pos._col >= 1 && pos._col <= 8) && (pos._row >= 1 && pos._row <= 8);
}

bool King::move(square tgt) const {
    if (!on_board(tgt)) return false;
    if (_pos == tgt) return false;
    bool horz = tgt._col >= _pos._col - 1 && tgt._col <= _pos._col + 1;
    bool vert = tgt._row >= _pos._row - 1 && tgt._row <= _pos._row + 1;
    return horz && vert;
}

bool Queen::move(square tgt) const {
    if (!on_board(tgt)) return false;
    if (_pos == tgt) return false;
    bool line = (tgt._col == _pos._col) || (tgt._row == _pos._row);
    bool diag = abs(_pos._col - tgt._col) == abs(_pos._row - tgt._row);
    return line || diag;
}

bool Rook::move(square tgt) const {
    if (!on_board(tgt)) return false;
    if (_pos == tgt) return false;
    return (tgt._col == _pos._col) || (tgt._row == _pos._row);
}

bool Bishop::move(square tgt) const {
    if (!on_board(tgt)) return false;
    if (_pos == tgt) return false;
    return abs(_pos._col - tgt._col) == abs(_pos._row - tgt._row);
}

bool Knight::move(square tgt) const {
    if (!on_board(tgt)) return false;
    if (_pos == tgt) return false;
    bool vert = abs(_pos._row - tgt._row) == 2 && abs(_pos._col - tgt._col) == 1;
    bool horz = abs(_pos._row - tgt._row) == 1 && abs(_pos._col - tgt._col) == 2;
    return vert || horz;
}

int main () {
    ChessChecker cc;
    try {
        cc.get_req();
        cc.check_req();
    }
    catch(char const* exc) {
        std::cout << exc << std::endl;
    }
    return 0;
}