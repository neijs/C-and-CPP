#include <iostream>
#include <stack>

int main() {
    std::stack<int> stack;
    char c;
    int a, b, num = 0;
    while ((c = std::cin.get()) != '\n') {
        if (c == '+' || c == '-' || c == '*' || c == '/') {
            b = stack.top(); stack.pop();
            a = stack.top(); stack.pop();
            switch (c) {
                case '+':
                    stack.push(a + b);
                    break;
                case '-':
                    stack.push(a - b);
                    break;
                case '*':
                    stack.push(a * b);
                    break;
                case '/':
                    stack.push(a / b);
                    break;
            };
        } else if (c != ' ') {
            num = num * 10 + c - '0';
        } else if (c == ' ') {
            if (num) stack.push(num);
            num = 0;
        }
    }
    std::cout << stack.top() << std::endl;
    stack.pop();
    return 0;
}