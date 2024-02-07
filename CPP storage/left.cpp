#include <iostream>
#include <string.h>
#include <cmath>
using namespace std;
#define LEN 101

char *left(char *str, int N) {
    char *ptr = str;
    if (N < 0)
        *str = '\0';
    for (; N-- && *str != '\0'; str++); 
    *str = '\0';
    return ptr;
}

unsigned long left(unsigned long num, int N) {
    if (N < 0)
        return 0;
    unsigned long tmp;
    int count = (num == 0) ? 1 : 0;
    for (tmp = num; tmp; tmp /= 10)
        count++;
    return (count < N) ? num : num / int(pow(10, count - N));
}

int main() {
    char choice[7];
    
    cin.getline(choice, 7);
    if (strcmp(choice, "string") == 0) {
        char string[LEN];
        int N;
        cin.getline(string, LEN);
        cin >> N;
        cout << left(string, N) << endl;
    } else if (strcmp(choice, "number") == 0){
        unsigned long num;
        int N;
        cin >> num;
        cin >> N;
        cout << left(num, N) << endl;
    }
    return 0;
}