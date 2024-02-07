#include <iostream>
#include <list>
#include <string>
#include <sstream>
#include <cstdlib>

int main(int argc, char** argv) {
    /* ~~~~~~~~~~~~~~~~~~~ */
    std::list<int> list;
    std::string str;
    std::getline(std::cin, str);
    std::istringstream sstr(str);
    int n;
    while (sstr >> n) list.push_back(n);
    /* ~~~~~~~~~~~~~~~~~~~ */
    std::list<int>::iterator iter = list.begin();
    if (argc == 4) {
        std::string cmd(argv[1]);
        if (cmd == "-ib") {
            for (; iter != list.end(); iter++)
                if (*iter == int(std::strtol(argv[3], NULL, 10))) {
                    list.insert(iter, int(std::strtol(argv[2], NULL, 10)));
                    break;
                }            
        } else if (cmd == "-ia") {
            for (; iter != list.end(); iter++)
                if (*iter == int(std::strtol(argv[3], NULL, 10))) {
                    std::advance(iter, 1);
                    list.insert(iter, int(std::strtol(argv[2], NULL, 10)));
                    break;
                }  
        }
    }
    else if (argc == 3) {
        std::string cmd(argv[1]);
        if (cmd == "-af") {
            list.push_front(int(std::strtol(argv[2], NULL, 10)));
        } else if (cmd == "-ae") {
            list.push_back(int(std::strtol(argv[2], NULL, 10)));
        } else if (cmd == "-d") {
            for (; iter != list.end(); iter++)
                if (*iter == int(std::strtol(argv[2], NULL, 10))) {
                    list.erase(iter);
                    break;
                }
        }
    }
    else if (argc == 2) {
        std::string cmd(argv[1]);
        if (cmd == "-sa") {
            list.sort();
        } else if (cmd == "-sd") {
            list.sort();
            list.reverse();
        } else if (cmd == "-mf" || cmd == "-me") {
            std::list<int>::iterator max_pos = iter;
            int max = *iter;
            for (++iter; iter != list.end(); iter++)
                if (*iter > max) {
                    max = *iter;
                    max_pos = iter; 
                }
            list.erase(max_pos);
            if (cmd == "-mf") list.push_front(max);
            else list.push_back(max);
        }
    }
    for (auto iter = list.begin(); iter != list.end(); iter++)
        std::cout << *iter << ' ';
    std::cout << std::endl;
    return 0;
}