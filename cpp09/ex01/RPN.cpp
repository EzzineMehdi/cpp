#include "RPN.hpp"

size_t	skipSeps(const std::string &str, const std::string &seps, size_t index)
{
	size_t	i = index;
	int		tmp;
	while (i < str.size())
	{
		tmp = seps.find(str[i]);
		if (tmp == -1)
			break ;
		i++;
	}
	return i;
}

std::string	getWord(const std::string &str, const std::string &seps, size_t &index)
{
	size_t	start = index;
	int		tmp;
	while (index < str.size())
	{
		tmp = seps.find(str[index]);
		if (tmp != -1)
			break ;
		index++;
	}
	return str.substr(start, index - start);
}

std::stack<std::string>	split(const std::string &str, const std::string &seps)
{
	size_t	i = 0;
	int		tmp = 0;
	
	std::stack<std::string>	con;

	while (i < str.size())
	{
		i = skipSeps(str, seps, i);
		if (i == str.size())
			break ;
		con.push(getWord(str, seps, i));
		if (isDigit(con.top()))
			tmp++;
		else if (isOperator(con.top()))
			tmp--;
		else
			throw std::runtime_error("Error: Operand out of syntax");
		if (tmp <= 0)
			throw std::runtime_error("Error: Syntax error");
	}
	if (tmp != 1)
		throw std::runtime_error("Error: Syntax error");
	return con;
}

double	calculator(double num[2], char op)
{
	char	ops[4] = {'+', '-', '*', '/'};
	int		c = 0;

	for (; c < 4; c++)
		if (op == ops[c])
			break ;

	switch (c)
	{
	case 0:
		return num[0] + num[1];
	case 1:
		return num[0] - num[1];
	case 2:
		return num[0] * num[1];
	default:
		return num[0] / num[1];
	}
}

bool isOperator(const std::string &op)
{
    if (op.size() == 1 && (op == "+" || op == "-" || op == "/" || op == "*"))
        return true;
    return false;
}

bool	isDigit(const std::string &op)
{
	size_t i = 0;
	if (op[i] == '+' || op[i] == '-')
		i++;
	if (!op[i])
		return false;
	if (op.substr(i).size() != 1 || !isdigit(op[i]))
		return false;
	return true;
}



RPN::RPN(char *av)
{
	std::stack<std::string> pure = split(av, " \t");

	while (pure.size())
	{
		op.push(pure.top());
		pure.pop();
	}
}


RPN::~RPN(){}

std::string to_string(double value) {
    std::stringstream oss;
    oss << value;
    return oss.str();
}

void   RPN::doOperation()
{
    char	o;
    double	n[2];
	std::stack<std::string>	re;

	while (!isOperator(op.top()))
	{
		re.push(op.top());
		op.pop();
	}
	o = op.top()[0];
	op.pop();
	n[1] = atof(re.top().c_str());
	re.pop();
	n[0] = atof(re.top().c_str());
	re.pop();
	op.push(to_string(calculator(n, o)));
	while (re.size())
	{
		op.push(re.top());
		re.pop();
	}
}

void RPN::runCalculator()
{
	while (op.size() != 1)
		doOperation();
	std::cout << atof(op.top().c_str()) << std::endl;
}
