#include<string>
#include<vector>
#include<stack>
#include<sstream>
#include <iostream>
#include <cstdlib>
using namespace std;

std::vector<std::string> split(std::string strToSplit, char delimeter)
{
    std::stringstream ss(strToSplit);
    std::string item;
	std::vector<std::string> splittedStrings;
    while (std::getline(ss, item, delimeter))
	{
		splittedStrings.push_back(item);
    }
	return splittedStrings;
}

bool verify(std::string strToVerify)
{
    for (int i = 0; i < strToVerify.size(); i++){
        if(strToVerify[i] < '0' && strToVerify[i] > '9' && strToVerify[i] != '+' && strToVerify[i] != '-' && strToVerify[i] != '*' && strToVerify[i] != '/')
        {
            return false;
        }
    }

    return true;
}

int main()
{
    std::cout << "Enter an arithmetic expression" << std::endl;

    std::string expression("Empty");

    std::cin >> expression;

    std::cout<<verify(expression)<<std::endl;

    if (verify(expression))
    {
        std::vector<std::string> split_plus = split(expression, '+');
        std::string expression_without_plus("");
        for (int i = 0; i < split_plus.size(); i++)
        {
            expression_without_plus += std::string("-") + split_plus[i];
        }

        std::string expression_minus = expression_without_plus.substr(1);
        std::vector<std::string> split_minus = split(expression_minus, '-');
        std::string expression_without_minus("");
        for (int i = 0; i < split_minus.size(); i++)
        {
            expression_without_minus += std::string("*") + split_minus[i];
        }

        std::string expression_times = expression_without_minus.substr(1);
        std::vector<std::string> split_times = split(expression_times, '*');
        std::string expression_without_times("");
        for (int i = 0; i < split_times.size(); i++)
        {
            expression_without_times += std::string("/") + split_times[i];
        }

        std::string expression_on = expression_without_times.substr(1);
        std::vector<std::string> split_on = split(expression_on, '/');

        std::vector<float> numbers;
        std::vector<char> ops;
        float temp = 0;

        for (int i = 0; i < split_on.size(); i++)
        {
            std::stringstream express(split_on[i]);
            express >> temp;
            numbers.push_back(temp);
            temp = 0;
        }
        for (int i = 0; i < expression.size(); i++)
        {
            if (expression[i] == '+' || expression[i] == '-' || expression[i] == '*' || expression[i] == '/')
            {
                ops.push_back(expression[i]);
            }
        }

        std::stack<float> mystack;
        mystack.push(numbers[0]);

        for (int i = 0; i < ops.size(); i++)
        {
            if(ops[i] == '*')
            {
                temp = mystack.top() * numbers[i+1];
                mystack.pop();
                mystack.push(temp);
            }
            else if(ops[i] == '/')
            {
                temp = mystack.top() / numbers[i+1];
                mystack.pop();
                mystack.push(temp);
            }
            else
            {
                mystack.push(numbers[i+1]);
            }
        }

        float final_result = mystack.top();
        mystack.pop();

        for (int i = ops.size()-1; i >= 0 && !mystack.empty(); i--)
        {
            if(ops[i] == '+')
            {
                final_result = mystack.top() + final_result;
                mystack.pop();
            }
            else if(ops[i] == '-')
            {
                final_result = mystack.top() - final_result;
                mystack.pop();
            }
        }
        std::cout<<final_result<<std::endl;
    }
    else
    {
        std::cout<<"Error !!! Your expression is invalid"<<std::endl;
    }

    /*int j = 1;
    int previous_time = 0;


    int final_result = result[0];

    for (int i = 0; i < expression.size(); i++)
    {
        if (expression[i] == '*')
        {
            final_result = final_result + result[j];
            j++;
        }
        else if (expression[i] == '-')
        {
            final_result = final_result - result[j];
            j++;
        }
        else
        {
            previous_time++;
        }
    }

    for (int i = 0; i < expression.size(); i++)
    {
        if (expression[i] == '+')
        {
            final_result = final_result + result[j];
            j++;
        }
        else if (expression[i] == '-')
        {
            final_result = final_result - result[j];
            j++;
        }
    }

    std::cout<<final_result<<std::endl;*/
    /*for (int i = 0; i < numbers.size(); i++)
    {
        std::cout<<numbers[i]<<std::endl;
    }
    for (int i = 0; i < ops.size(); i++)
    {
        std::cout<<ops[i]<<std::endl;
    }*/


    return 0;
}
