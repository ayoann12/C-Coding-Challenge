#include<string>
#include<vector>
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

int main()
{
    std::cout << "Enter an arithmetic expression" << std::endl;

    std::string expression("Empty");

    std::cin >> expression;

    std::vector<std::string> split_plus = split(expression, '+');
    std::string expression_without_plus("");
    for (int i = 0; i < split_plus.size(); i++)
    {
        expression_without_plus += std::string("-") + split_plus[i];
    }

    std::string expression_only_minus = expression_without_plus.substr(1);
    std::vector<std::string> split_minus = split(expression_only_minus, '-');
    std::vector<int> result;
    int temp = 0;

    for (int i = 0; i < split_minus.size(); i++)
    {
        std::stringstream express(split_minus[i]);
        express >> temp;
        result.push_back(temp);
        temp = 0;
    }
    int j = 1;


    int final_result = result[0];

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

    std::cout<<final_result<<std::endl;

    return 0;
}
