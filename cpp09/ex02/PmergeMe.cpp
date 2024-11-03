#include "PmergeMe.hpp"

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

std::vector<std::string>	split(const std::string str, const std::string seps)
{
	size_t	i = 0;
	size_t	it = 0;
	std::vector<std::string>	con;

	while (i < str.size())
	{
		i = skipSeps(str, seps, i);
		if (i == str.size())
			break ;
		con.push_back(getWord(str, seps, i));
		it++;
	}
	return con;
}

bool	isDigit(const std::string &str)
{
	size_t i = 0;
	if (str[i] == '+')
		i++;
	if (!str[i])
		return false;
	for (; i < str.size(); i++)
		if (!isdigit(str[i]))
			return false;
	return true;
}

void	fillVector(const std::vector<std::string> &parse, std::vector<int> &vc)
{
	double	v;
	for (size_t i = 0; i < parse.size(); i++)
	{
		if (!isDigit(parse[i]))
			throw std::runtime_error("Error: " + parse[i] + " is not a positif number");
		v = atof(parse[i].c_str());
		if (v > INT_MAX)
			throw std::runtime_error("Error: overflow on " + parse[i]);
		vc.push_back(v);
	}
}

int	sequence(int n)
{
	if (n == 0)
		return 0;
	if (n == 1)
		return 1;
	return sequence(n - 1) + 2 * sequence(n - 2);
}