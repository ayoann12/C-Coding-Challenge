#include<string>
#include<vector>
#include<stack>
#include<sstream>
#include <iostream>
#include <cstdlib>
#include <typeinfo>
using namespace std;

float error = 0.0110011;

int priority(char op){
    if(op == '+' || op == '-')
    {
        return 1;
    }

    if(op == '*'||op == '/')
    {
        return 2;
    }

    return 0;
}

float operation(char op, float number1, float number2)
{
    switch (op)
    {
        case '+':
            return number1 + number2;
            break;
        case '-':
            return number1 - number2;
            break;
        case '*':
            return number1 * number2;
            break;
        case '/':
            return number1 / number2;
            break;
        default:
            return error;
            break;
    }
}


int main()
{
    std::cout << "Enter an arithmetic expression" << std::endl;

    std::string expression("Empty");

    std::cin >> expression;

    expression = std::string("(") + expression + std::string(")");

    std::stack<float> numbers;

    std::stack<char> ops;

    int i = 0;

    int temp = 0;

    float number = 0;

    while(i < expression.size())
    {
        if(expression[i] == '(')
        {
            std::cout<<"Case 1 : opening brace"<<std::endl;
            ops.push(expression[i]);
            i++;
        }

        else if(isdigit(expression[i]))
        {
            std::cout<<"Case 2 : digit"<<std::endl;
            while(isdigit(expression[i]) && i < expression.size())
            {
                number = number * 10 + (expression[i] - '0');
                i++;
            }
            numbers.push(number);
            number = 0;
        }

        else if(expression[i] == ')')
        {
            std::cout<<"Case 3 : closing brace"<<std::endl;
            while(!ops.empty() && ops.top() != '(')
            {
                float value2 = numbers.top();
                numbers.pop();

                float value1 = numbers.top();
                numbers.pop();

                char op = ops.top();
                ops.pop();

                numbers.push(operation(op, value1, value2));
            }
            // pop opening brace.
            ops.pop();
            i++;
        }

        else
        {
            if(operation(expression[i], 0, 0) == error)
            {
                std::cout<<"Expression invalide !"<<std::endl;
                return 0;
            }
            else
            {
                std::cout<<"Case 4 : operation"<<std::endl;
                while(!ops.empty() && priority(ops.top()) >= priority(expression[i]))
                {
                    float value2 = numbers.top();
                    numbers.pop();

                    float value1 = numbers.top();
                    numbers.pop();

                    char op = ops.top();
                    ops.pop();

                    numbers.push(operation(op, value1, value2));
                }
                ops.push(expression[i]);
            }
            i++;

        }
        std::cout<<i<<std::endl;
    }

    std::cout<<numbers.top()<<std::endl;

    return 0;
}
