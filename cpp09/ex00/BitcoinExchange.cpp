#include "BitcoinExchange.hpp"

typedef BitcoinExchange::Date	Date;

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

std::map<size_t, std::string>	split(const std::string &str, const std::string &seps)
{
	size_t	i = 0;
	size_t	it = 0;
	std::map<size_t, std::string>	con;

	while (i < str.size())
	{
		i = skipSeps(str, seps, i);
		if (i == str.size())
			break ;
		con[it] = getWord(str, seps, i);
		it++;
	}
	return con;
}

void	checkDateFormat(int	date[3])
{
	if (date[1] > 12 || date[2] > 31)
		throw std::runtime_error("Error: invalid date format");
}

size_t	countChar(const std::string &str, char c)
{
	size_t	cn = 0;
	for (size_t i = 0; i < str.size(); i++)
		if (str[i] == c)
			cn++;
	return cn;
}


BitcoinExchange::Date::Date(const Date &other)
{
	for (int i = 0; i < 3; i++)
		date[i] = other.date[i];
}

void	checkNmber(const std::string &str)
{
	double	tmp;

	std::map<size_t, std::string> strs = split(str, " \t");
	if (strs.size() != 1 || !isDigit(strs[0]))
		throw std::runtime_error("Error: " + str + " is not a number");
	tmp = atof(str.c_str());
	if (tmp > INT_MAX)
		throw std::runtime_error("Error: overflow");
}

BitcoinExchange::Date::Date(const  std::string &str)
{
	std::map<size_t, std::string> strs = split(str, "-");
	if (strs.size() != 3 || countChar(str, '-') != 2)
		throw std::runtime_error("Error: invalid date format");
	for (int i = 0; i < 3; i++)
	{
		checkNmber(strs[i]);
		date[i] = atoi(strs[i].c_str());
		if (!date[i])
			throw std::runtime_error("Error: invalid date format");
	}
	checkDateFormat(date);
}


BitcoinExchange::Date::~Date(){}


bool	BitcoinExchange::Date::operator<(const Date &other) const
{
	if (date[0] < other.date[0])
		return true;
	else if (date[0] == other.date[0])
	{
		if (date[1] < other.date[1])
			return true;
		else if (date[1] == other.date[1])
		{
			if (date[2] < other.date[2])
				return true;
			else
				return false;
		}
		else
			return false;
	}
	else
		return false;
}


void BitcoinExchange::Date::showDate(std::ostream &c) const
{
	c << date[0] << "-" << std::setw(2) << std::setfill('0') << date[1]
		<< "-" << std::setw(2) << std::setfill('0') << date[2];
}


BitcoinExchange::BitcoinExchange()
{
	std::ifstream	file("data.csv");
	std::string		str;
	std::map<size_t, std::string>	strs;

	if (!file.is_open())
		throw std::runtime_error("Error: can't open data.csv");

	getline(file, str);
	while (getline(file, str))
	{
		strs = split(str, ",");
		data[Date(strs[0])] = atof(strs[1].c_str());
	}
}

BitcoinExchange::~BitcoinExchange(){}

double	BitcoinExchange::getPrice(const Date &date) const
{
	if (date < data.begin()->first)
		return data.begin()->second;

	std::map<Date, double>::const_iterator it = data.upper_bound(date);

	if (it != data.end())
		it--;
	else
		it = --data.end();

	return it->second;
}

std::ostream &operator<<(std::ostream &s, const Date &date)
{
	date.showDate(s);
	return s;
}