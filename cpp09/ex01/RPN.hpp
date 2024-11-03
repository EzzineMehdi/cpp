#ifndef RPN_
#define RPN_

#include <iostream>
#include <stack>
#include <cstdlib>
#include <sstream>

class RPN
{
	private:
		std::stack<std::string> op;
		RPN();
		RPN(const RPN &other);

		RPN	&operator=(const RPN &other);
	public:
		RPN(char *av);

		~RPN();

		void   doOperation();
		void runCalculator();
};

std::stack<std::string>	split(const std::string &str, const std::string &seps);
double	calculator(double num[2], char op);
bool isOperator(const std::string &op);
bool	isDigit(const std::string &op);

#endif