#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <sstream>
#include <cctype>
#include <cmath>

bool isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
}

int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    if (op == '^') return 3;
    return 0;
}

std::string infixtopostfix(std::string& exp) {
    std::string post;
    std::stack<char> opStack;
    int len = exp.length();

    for (int i = 0; i < len; i++) {
        if (isdigit(exp[i])) {
            // Handle multi-digit numbers
            while (i < len && isdigit(exp[i])) {
                post += exp[i++];
            }
            post += ' ';
            i--; // adjust loop increment
        }
        else if (exp[i] == '(') {
            opStack.push(exp[i]);
        }
        else if (exp[i] == ')') {
            while (!opStack.empty() && opStack.top() != '(') {
                post += opStack.top();
                post += ' ';
                opStack.pop();
            }
            if (!opStack.empty()) opStack.pop(); // pop '('
        }
        else if (isOperator(exp[i])) {
            while (!opStack.empty() && precedence(opStack.top()) >= precedence(exp[i])) {
                post += opStack.top();
                post += ' ';
                opStack.pop();
            }
            opStack.push(exp[i]);
        }
    }

    while (!opStack.empty()) {
        post += opStack.top();
        post += ' ';
        opStack.pop();
    }

    return post;
}

int calculation(const std::string postfix) {
    std::stack<double> operandStack;
    std::stringstream ss(postfix);
    std::string token;

    while (ss >> token) {
        if (isdigit(token[0]) || (token.length() > 1 && token[0] == '-')) {
            operandStack.push(std::stod(token));
        }
        else if (isOperator(token[0])) {
            if (operandStack.size() < 2) {
                std::cerr << "Error: insufficient operands\n";
                return 0;
            }
            double op1 = operandStack.top(); operandStack.pop();
            double op2 = operandStack.top(); operandStack.pop();
            double result;

            switch (token[0]) {
                case '+': result = op2 + op1; break;
                case '-': result = op2 - op1; break;
                case '*': result = op2 * op1; break;
                case '/': result = op2 / op1; break;
                case '^': result = std::pow(op2, op1); break;
                default: result = 0;
            }
            operandStack.push(result);
        }
    }

    if (!operandStack.empty())
        return operandStack.top();
    else {
        std::cerr << "Error: invalid expression\n";
        return 0;
    }
}

int main() {
    std::string exp;
    std::cout << "Enter the infix expression: ";
    std::getline(std::cin, exp);

    std::string postfix = infixtopostfix(exp);
    std::cout << "Postfix: " << postfix << std::endl;

    double result = calculation(postfix);
    std::cout << "Result: " << result << std::endl;

    return 0;
}
