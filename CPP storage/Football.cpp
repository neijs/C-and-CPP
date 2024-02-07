#include <iostream>
#include <cstring>
#define TEAMSIZE 11

class Player {
    char _team[6];
    int _num;
public:
    Player(char const* team, int num);
    ~Player();
    void Print() const;
    static void Print_teams();
private:
    static int zenit[TEAMSIZE];
    static int cska[TEAMSIZE];
    static void print_team(int* const team, char const* name);
    static void checkin(int* const team, int num, char const* name);
    static void checkout(int* const team, int num);
};

class def_exc {
    char* _type;
    char* _team;
public:
    def_exc(char const* type, char const* team);
    virtual ~def_exc() { delete[] _type; delete[] _team; }
    virtual void what() const;
};

class player_exc : public def_exc {
    char* _type;
    char* _team;
    int _player;
public:
    player_exc(char const* type, char const* team, int player);
    virtual ~player_exc() { delete[] _type; delete[] _team; }
    virtual void what() const;
};

int Player::zenit[TEAMSIZE] = {0,0,0,0,0,0,0,0,0,0,0};
int Player::cska[TEAMSIZE] = {0,0,0,0,0,0,0,0,0,0,0};

Player::Player(char const* team, int num) {
    if (std::strcmp(team, "CSKA") == 0)
        checkin(cska, num, "CSKA");
    else if (std::strcmp(team, "Zenit") == 0)
        checkin(zenit, num, "Zenit");
    else
        throw def_exc("Wrong name", team);
    _num = num;
    std::strcpy(_team, team);
}

Player::~Player() {
    if (std::strcmp(_team, "CSKA") == 0)
        checkout(cska, _num);
    else // Zenit
        checkout(zenit, _num);
}

void Player::Print() const {
    std::cout << _team << " " << _num << std::endl;
}

void Player::Print_teams() {
    print_team(zenit, "Zenit");
    print_team(cska, "CSKA");
}

void Player::print_team(int* const team, char const* name) {
    if (team[0] == 0) return;
    std::cout << name << ": ";
    for (int i = 0; team[i] != 0; ++i)
        std::cout << team[i] << " ";
    std::cout << std::endl;
}

void Player::checkin(int* const team, int num, char const* name) {
    if (num < 1) throw player_exc("Wrong number", name, num);
    int i;
    for (i = 0; team[i] != 0 && i < TEAMSIZE; ++i)
        if (team[i] == num) throw player_exc("Double number", name, num);
    if (team[TEAMSIZE - 1]) throw def_exc("Too many players", name);
    team[i] = num;
}

void Player::checkout(int* const team, int num) {
    int i;
    for (i = 0; team[i] != num; ++i);
    for (int j = i; team[j] != 0 && j < TEAMSIZE; ++j) 
        team[j] = team[j + 1];
    team[TEAMSIZE - 1] = 0;
}

/* ~~~~ def_exc and player_exc realization ~~~~ */

def_exc::def_exc(char const* type, char const* team) {
    _type = new char[std::strlen(type) + 1];
    _team = new char[std::strlen(team) + 1];
    std::memcpy(_type, type, std::strlen(type));
    std::memcpy(_team, team, std::strlen(team));
}

void def_exc::what() const {
    std::cerr << "Exception: " << _type << " in team " << _team;
}

player_exc::player_exc(char const* type, char const* team, int player) : def_exc(type, team)
    { _player = player; }

void player_exc::what() const {
    def_exc::what();
    std::cerr << " Error number: " << _player;
}

void test_players();

int main() {
    try {
        test_players();
    }
    catch(def_exc const& exc) {
        exc.what();
        std::cerr << std::endl;
    }
    return 0;
}