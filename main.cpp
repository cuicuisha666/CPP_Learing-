#include <iostream>
#include <string>
#include <stack>
#include <cmath>
#include <sstream>
#include <vector>

// 定义运算符的优先级
int getPriority(char op) {
    if (op == '+' || op == '-') {
        return 1;
    } else if (op == '*' || op == '/') {
        return 2;
    } else if (op == '^') {
        return 3;
    }
    return 0; // 对于括号，优先级最高
}

// 执行简单的二元运算
double applyOperator(double a, double b, char op) {
    if (op == '+') {
        return a + b;
    } else if (op == '-') {
        return a - b;
    } else if (op == '*') {
        return a * b;
    } else if (op == '/') {
        return a / b;
    } else if (op == '^') {
        return pow(a, b);
    }
    return 0;
}

// 将中缀表达式转换为后缀表达式，并处理 x[1] 或者 x[0] 这样的表达式
std::string infixToPostfix(const std::string& infixExpr, const std::vector<double>& x) {
    std::stack<char> opStack;
    std::string postfixExpr;

    std::istringstream iss(infixExpr); //输出字符串流

    char c;
    while (iss >> c) {
        if (c == ' ') {
            continue;
        }
        // 遇到小数点继续读入
        if (isdigit(c) || c == '.') {
            postfixExpr += c;
        } else if (c == 'x') {
            std::string indexStr;
            iss >> c; // 读取 '['
            while (iss >> c) {
                if (isdigit(c)) {
                    indexStr += c;
                } else if (c == ']') {
                    int index = std::stoi(indexStr); // stoi（）将字符串 str 转成 int 整数
                    double val = x[index];
                    postfixExpr += std::to_string(val); // 再将得出的x[]的值转化为string字符串读入postfixExpr
                    break;
                }
            }
        } else if (c == '(') {
            opStack.push(c);
        } else if (c == ')') {
            while (!opStack.empty() && opStack.top() != '(') {
                postfixExpr += ' ';
                postfixExpr += opStack.top();
                opStack.pop();
            }
            if (!opStack.empty() && opStack.top() == '(') {
                opStack.pop();
            }
        } else {
            while (!opStack.empty() && getPriority(opStack.top()) >= getPriority(c)) {
                postfixExpr += ' ';
                postfixExpr += opStack.top();
                opStack.pop();
            }
            postfixExpr += ' ';
            opStack.push(c);
        }
    }

    while (!opStack.empty()) {
        postfixExpr += ' ';
        postfixExpr += opStack.top();
        opStack.pop();
    }

    return postfixExpr;
}


// 计算 postfix 表达式的结果
double calculatePostfix(const std::string& postfixExpr) {
    std::stack<double> numStack;

    std::istringstream iss(postfixExpr);
    std::string token;

    while (iss >> token) {
        if (isdigit(token[0]) || token[0] == '.') {
            double num;
            std::istringstream(token) >> num;
            numStack.push(num);
        } else {
            double num2 = numStack.top();
            numStack.pop();
            double num1 = numStack.top();
            numStack.pop();
            double result = applyOperator(num1, num2, token[0]);
            numStack.push(result);
        }
    }

    return numStack.top();
}

int main() {
    std::vector<double> x = {1.7, 7.5, 2.1}; // 假设 x 是一个 vector 数组，里面存放着对应的数值

    std::string functionExpr = "x[1]+3*(x[0]+x[2])";
    std::cout << "原始字符串为: " << functionExpr << std::endl;

    // 将中缀表达式转换为后缀表达式，并将 vector 数组 x 作为参数传递
    std::string postfixExpr = infixToPostfix(functionExpr, x);
    std::cout << "转换后的后缀表达式为: " << postfixExpr << std::endl;

    // 计算后缀表达式的结果
    double result = calculatePostfix(postfixExpr);
    std::cout << "计算结果为: " << result << std::endl;

    return 0;
}
