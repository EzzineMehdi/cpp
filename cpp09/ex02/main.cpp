#include "PmergeMe.hpp"

int main(int ac, char **av)
{
	if (ac < 2)
	{
		std::cout << "No args available" << std::endl;
		return 1;
	}

	try
	{
		PmergeMe< std::vector<int>, std::vector< std::pair<int, int> > >	vector;
		PmergeMe< std::deque<int>, std::deque< std::pair<int, int> > >		deque;

		vector.setData(ac, av);
		deque.setData(ac, av);
		vector.show("before");
		vector.runAlgo();
		deque.runAlgo();
		vector.show("after");
		std::cout << "Time to process a range of	"
			<< (ac - 1) << " elements with std::vector : " << std::fixed << vector.getTime() << " us" << std::endl;
		std::cout << "Time to process a range of	"
			<< (ac - 1) << " elements with std::deque : " << std::fixed << deque.getTime() << " us" << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}

	return 0;
}
