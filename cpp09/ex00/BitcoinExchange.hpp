#ifndef BE_HPP
#define BE_HPP

#include <iostream>
#include <fstream>
#include <map>
#include <cstdlib>
#include <iomanip>
#include <limits.h>

class BitcoinExchange
{
	public:
		class	Date
		{
			private:
				int	date[3];

				Date();

				Date	&operator=(const Date& other);
			public:
				Date(const  std::string &str);
				Date(const Date& other);

				~Date();

				bool	operator<(const Date &other) const;
				void	showDate(std::ostream &c) const;
		};
		BitcoinExchange();

		~BitcoinExchange();

		double	getPrice(const Date &date) const;

	private:
		std::map<Date, double>	data;

		BitcoinExchange(const BitcoinExchange &other);
		BitcoinExchange	&operator=(const BitcoinExchange &other);
};

typedef BitcoinExchange::Date	Date;

size_t							countChar(const std::string &str, char c);
std::map<size_t, std::string>	split(const std::string &str, const std::string &seps);
std::ostream					&operator<<(std::ostream &s, const Date & date);
bool							isDigit(const std::string &str);

#endif