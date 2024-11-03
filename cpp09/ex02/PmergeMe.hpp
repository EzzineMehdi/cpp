#ifndef PMERGEME
#define PMERGEME

#include <ctime>
#include <iostream>
#include <vector>
#include <deque>
#include <sys/time.h>
#include <sstream>
#include <cstdlib>
#include <limits.h>

template<typename IntCon, typename PairCon>
class PmergeMe
{
    private:
		IntCon				toSort;
		std::clock_t	time;
        typedef typename  IntCon::iterator	iterator;
        typedef typename  PairCon::iterator	piterator;

        PmergeMe(const PmergeMe &other);

        PmergeMe    &operator=(const PmergeMe &other);
    public:
        PmergeMe();

        ~PmergeMe();

        int         binarySearchP(piterator cBegin, piterator cEnd, int a) const;
        void        insertP(piterator pos, piterator add) const;
        void	    insertionSortP(PairCon &v) const;
	
		int         binarySearch(iterator cBegin, iterator cEnd, int a) const;
        void        insert(iterator pos, iterator add) const;
        void	    insertionSort(IntCon &v) const;
		void		mergePairs(PairCon &container, PairCon &content) const;
		PairCon		mergeSort(const PairCon &toSort, int eGroup);

        void	    merge(IntCon &largest, IntCon &lowest, int start, int end) const;
		PairCon		createPairs();
		IntCon		jacobsthalSequence(int n) const;
        IntCon      sortAlgo();
		void		setData(int ac, char **av);
		void		show(std::string	msg);
		void		runAlgo();
		double		getTime() const;
};

std::vector<std::string>	split(const std::string str, const std::string seps);
void						fillVector(const std::vector<std::string> &parse, std::vector<int> &vc);
int							sequence(int n);

template<typename IntCon, typename PairCon>
PmergeMe<IntCon, PairCon>::PmergeMe(){}


template<typename IntCon, typename PairCon>
PmergeMe<IntCon, PairCon>::~PmergeMe(){}


//PairCon
template<typename IntCon, typename PairCon>
int         PmergeMe<IntCon, PairCon>::binarySearchP(piterator cBegin, piterator cEnd, int a) const
{
	piterator	begin = cBegin;
	piterator	end = cEnd;
	piterator	mid;

	if (a == end->first || a == begin->first)
		return a == end->first ? (end - cBegin) : 0;

	if (a > end->first || a < begin->first)
		return a > end->first ? (end - cBegin) : -1;

	while (end - begin > 1)
	{
		mid = begin + (end - begin + 1) / 2;
		if (a > mid->first)
			begin = mid;
		else if (a < mid->first)
			end = mid;
		else
			return mid - cBegin;
	}
	return begin - cBegin;
}

template<typename IntCon, typename PairCon>
void        PmergeMe<IntCon, PairCon>::insertP(piterator pos, piterator add) const
{
    int	i1 = add->first;
    int	i2 = add->second;
	for (;add > pos;add--)
	{
		add->first = (add - 1)->first;
		add->second = (add - 1)->second;
	}
	pos->first = i1;
	pos->second = i2;
}

template<typename IntCon, typename PairCon>
void	    PmergeMe<IntCon, PairCon>::insertionSortP(PairCon &v) const
{
	piterator	end = v.begin();
	int			index;

	for (piterator	add = end + 1; add != v.end(); end++, add++)
	{
		index = binarySearchP(v.begin(), end, add->first) + 1;
		insertP(v.begin() + index, add);
	}
}

//IntCon
template<typename IntCon, typename PairCon>
int         PmergeMe<IntCon, PairCon>::binarySearch(iterator cBegin, iterator cEnd, int a) const
{
	iterator	begin = cBegin;
	iterator	end = cEnd;
	iterator	mid;

	if (a == *end || a == *begin)
		return a == *end ? (end - cBegin) : 0;

	if (a > *end || a < *begin)
		return a > *end ? (end - cBegin) : -1;

	while (end - begin > 1)
	{
		mid = begin + (end - begin + 1) / 2;
		if (a > *mid)
			begin = mid;
		else if (a < *mid)
			end = mid;
		else
			return mid - cBegin;
	}
	return begin - cBegin;
}

//ttt

template<typename IntCon, typename PairCon>
void        PmergeMe<IntCon, PairCon>::insert(iterator pos, iterator add) const
{
    int	tmp = *add;

	for (;add > pos;add--)
		*add = *(add - 1);
	*pos = tmp;
}

template<typename IntCon, typename PairCon>
void	    PmergeMe<IntCon, PairCon>::insertionSort(IntCon &v) const
{
	iterator	end = v.begin();
	int			index;

	for (iterator	add = end + 1; add != v.end(); end++, add++)
	{
		index = binarySearch(v.begin(), end, *add) + 1;
		insert(v.begin() + index, add);
	}
}

template <typename IntCon, typename PairCon>
void PmergeMe<IntCon, PairCon>::mergePairs(PairCon &container, PairCon &content) const
{
    int			index;
	piterator	cBegin;

	if (container.size() == 0)
	{
		container = content;
		return ;
	}

	cBegin = container.begin();

	for (piterator i = content.begin(); i != content.end(); i++)
	{
		index = binarySearchP(cBegin, container.end() - 1, i->first) + 1;
		container.insert(cBegin + index, *i);
		cBegin = container.begin() + index;
	}
}

template <typename IntCon, typename PairCon>
PairCon PmergeMe<IntCon, PairCon>::mergeSort(const PairCon &toSort, int eGroup)
{
	PairCon	righPart;
	PairCon	leftPart;
	int					size = toSort.size();

	if (!size)
		return righPart;
	if (size >= eGroup)
		size = eGroup;
	righPart = mergeSort(PairCon(toSort.begin() + size, toSort.end()), eGroup);
	leftPart.insert(leftPart.begin(), toSort.begin(), toSort.begin() + size);

	insertionSortP(leftPart);

	mergePairs(righPart, leftPart);

	return righPart;
}

template<typename IntCon, typename PairCon>
void	    PmergeMe<IntCon, PairCon>::merge(IntCon &largest, IntCon &lowest, int start, int end) const
{
    int			index;

	for (int i = end; i >= start; i--)
	{
		if(i >= 0 && i < static_cast<int>(lowest.size()))
		{
			index = binarySearch(largest.begin(), largest.end() - 1, lowest[i]) + 1;
			largest.insert(largest.begin() + index, lowest[i]);
		}
	}
}

template<typename IntCon, typename PairCon>
PairCon	PmergeMe<IntCon, PairCon>::createPairs()
{
	PairCon	p;

	for (iterator i = toSort.begin(); i != toSort.end(); i += 2)
		*i > *(i + 1)? p.push_back(std::pair<int, int>(*i, *(i + 1)))
			: p.push_back(std::pair<int, int>(*(i + 1), *i));
	
	return mergeSort(p, 4);
}

template <typename IntCon, typename PairCon>
IntCon PmergeMe<IntCon, PairCon>::jacobsthalSequence(int n) const
{
	IntCon	v;

	for (int i = 2;; i++)
	{
		v.push_back(sequence(i));
		if (v.back() > n)
			break ;
	}
	return v;
}

template<typename IntCon, typename PairCon>
IntCon PmergeMe<IntCon, PairCon>::sortAlgo()
{
	PairCon pairHolder = createPairs();
	IntCon	largest;
	IntCon	lowest;
	
	for(size_t i = 0;i < pairHolder.size();i++)
	{
		largest.push_back(pairHolder[i].first);
		lowest.push_back(pairHolder[i].second);
	}


	int		n = largest.size();
	IntCon 	seq = jacobsthalSequence(n);
	int			start = 0;
	int			end;

	for (int i = 0;; i++)
	{
		end = seq[i] - 1;
		merge(largest, lowest, start, end);
		start = end + 1;
		if (start >= n)
			break ;
	}
	return largest;
}

template<typename IntCon, typename PairCon>
void PmergeMe<IntCon, PairCon>::setData(int ac, char **av)
{
	std::vector<int>				v;
	std::vector<std::string>		parse;

	for (int i = 1; i < ac; i++)
	{
		parse = split(av[i], " \t");
		fillVector(parse, v);
	}
	if (!v.size())
		throw std::runtime_error("Error: empty args");
	toSort.insert(toSort.begin(), v.begin(), v.end());
}

template<typename IntCon, typename PairCon>
void PmergeMe<IntCon, PairCon>::show(std::string msg)
{
	std::cout << msg << ":	";
	for (typename IntCon::iterator i = toSort.begin(); i != toSort.end(); i++)
		std::cout << *i << " ";
	std::cout << std::endl;
}

template<typename IntCon, typename PairCon>
void PmergeMe<IntCon, PairCon>::runAlgo()
{
	time = std::clock();
	if (toSort.size() == 1)
	{
		time = std::clock() - time;
		return ;
	}

	int	tmp = -1;

	if (toSort.size() % 2)
	{
		tmp = toSort.back();
		toSort.resize(toSort.size() - 1);
	}
	toSort = sortAlgo();

	if (tmp != -1)
	{
		int index = binarySearch(toSort.begin(), toSort.end() - 1, tmp) + 1;
		toSort.insert(toSort.begin() + index, tmp);
	}

	time = std::clock() - time;
}

template<typename IntCon, typename PairCon>
double PmergeMe<IntCon, PairCon>::getTime() const
{
	return time / (double) CLOCKS_PER_SEC;
}

#endif