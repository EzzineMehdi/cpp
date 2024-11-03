#include "RPN.hpp"

int main(int ac, char **av)
{
	if (ac != 2)
	{
		std::cout << "invalid args\n";
		return 1;
	}

	try
	{
		RPN a(av[1]);

		a.runCalculator();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}

    return 0;
}