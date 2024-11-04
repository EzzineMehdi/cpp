#include "BitcoinExchange.hpp"

bool	isFloat(const std::string &str)
{
	std::map<size_t, std::string>	strs = split(str, ".");

	if (countChar(str, '.') != 1 || strs.size() != 2)
		return false;
	if (!isDigit(strs[0]) || !isDigit(strs[1]))
		return false;
	return true;
}

void	parseInput(const std::string &str, const BitcoinExchange &b)
{
	double	data[2];
	std::map<size_t, std::string>	strs = split(str, "|");

	if (countChar(str, '|') != 1 || strs.size() != 2)
		throw std::runtime_error("Error: bad input => " + str);
	
	Date date(strs[0]);
		data[0] = b.getPrice(date);
	if (!isDigit(strs[1]) && !isFloat(strs[1]))
		throw std::runtime_error("Error: bad input => " + str);
	data[1] = atof(strs[1].c_str());
	if (data[1] < 0 || data[1] > 1000)
		throw data[1] < 0 ? std::runtime_error("Error: not a positive number.")
			: std::runtime_error("Error: too large number.");
	std::cout << date << " => " << data[1] << " = " << data[0] * data[1] << std::endl;
}

void	parseFirstLine(const std::string &str)
{
	std::string						data[2] = {"date", "value"};
	std::map<size_t, std::string>	strs = split(str, "|");
	std::map<size_t, std::string>	words;

	if (countChar(str, '|') != 1 || strs.size() != 2)
		throw std::runtime_error("Error: first line error");
	for (int i = 0; i < 2; i++)
	{
		words = split(strs[i], " \t");
		if (words.size() != 1 || words[0] != data[i])
			throw std::runtime_error("Error: first line error");
	}
}

int	main(int ac, char **av)
{
	if (ac != 2)
	{
		std::cout << "invalid args\n";
		return 1;
	}

	try
	{
		BitcoinExchange b;
		std::ifstream file(av[1]);
		if (!file.is_open())
		{
			std::cout << "can't open " << av[1] << std::endl;
			return 1;
		}

		std::cout.precision(10);
		std::string	str;
		getline(file, str);
		parseFirstLine(str);
		while (getline(file, str))
		{
			if (!str.size())
				continue ;
			try
			{
				parseInput(str, b);
			}
			catch(const std::exception& e)
			{
				std::cout << e.what() << std::endl;
			}
		}
	}
	catch(const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return 1;
	}
	
	return 0;
}
