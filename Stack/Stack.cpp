#include <iostream>
#include <stack>
#include <sstream>
#include <stdexcept>
#include <cmath>

double applyOperator(const std::string& op, double a, double b) {
    if (op == "+") return a + b;
    if (op == "-") return a - b;
    if (op == "*") return a * b;
    if (op == "/") {
        if (b == 0) throw std::runtime_error("Division by zero error");
        return a / b;
    }
    if (op == "^") return std::pow(a, b);
    throw std::runtime_error("Invalid operator");
}

double evaluatePostfix(const std::string& expression) {
    std::stack<double> stack;
    std::istringstream tokens(expression);
    std::string token;

    while (tokens >> token) {
        if (std::isdigit(token[0]) || (token[0] == '-' && token.size() > 1)) {
            stack.push(std::stod(token));
        }
        else {
            if (stack.size() < 2) throw std::runtime_error("Invalid expression");
            double b = stack.top(); stack.pop();
            double a = stack.top(); stack.pop();
            double result = applyOperator(token, a, b);
            stack.push(result);
        }
    }

    if (stack.size() != 1) throw std::runtime_error("Invalid expression");
    return stack.top();
}

int main() {
    std::string expression;
    std::cout << "Enter a postfix expression: ";
    std::getline(std::cin, expression);

    try {
        double result = evaluatePostfix(expression);
        std::cout << "Result: " << result << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
