#include<string>
#include<stack>
#include <iostream>
using namespace std;

/*
    "error" is a code that is returned when an unexpected character is found
    (everything but digits or operands or braces)
*/
float error = 0.0110011;


/*
    "priority" is a function that ranks the operand's priority. So "*" and "/" are prior over "+" and "-",
    and those last are prior and opening brace
*/
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

/*
    "operation" is a function that applies the operation, according to the operand.
    It detects also unexpected characters and returns error code
*/
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

    // We add braces all around the expression for better processing
    expression = std::string("(") + expression + std::string(")");

    // "numbers" is a stack to store the numbers of the expression. "ops" stores braces and operands.
    std::stack<float> numbers;
    std::stack<char> ops;

    // "number" stores current number before stacking it
    float number = 0;
    int i = 0;


    while(i < expression.size())
    {
        if(expression[i] == '(')
        {
            ops.push(expression[i]);
            i++;
        }

        else if(isdigit(expression[i]))
        {
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
            /*
                When the program finds a closing brace, it computes everything before until the very previous opening brace.
                It pops also everything computed and stacks the result
            */
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

            // It pops also the opening brace
            ops.pop();
            i++;
        }

        else
        {
            /*
                if error code is returned or two operands are following, the program stops
            */
            if(operation(expression[i], 0, 0) == error || !isdigit(expression[i-1]))
            {
                std::cout<<"Invalid expression!"<<std::endl;
                return 0;
            }

            /*
                else it computes the two numbers on top if the priority is correct
            */
            else
            {
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
    }

    // Normally, the final result only is in the stack
    float result = numbers.top();
    numbers.pop();

    // Else, the program stops with an error
    if (!numbers.empty())
    {
        std::cout<<"Invalid expression!"<<std::endl;
        return 0;
    }

    std::cout<<result<<std::endl;

    return 0;
}
