#include <deque>
#include <utility>

typedef std::deque<int> dq;


// template <typename Pair>
// std::pair<Pair, Pair>

template <typename T> // pair<int, int>... pair< pair<int, int>, pair<int, int> >...
std::deque<T> dividePairsAndSort(std::deque<T> sequence, unsigned int recursionLevel = 1) {

	if (sequence.size() < 2)
		return sequence;

	// Swap elements having the biggest first for every future couple
	for (typename std::deque<T>::iterator it = sequence.begin();
			it != sequence.end() && it + 1 != sequence.end();
			it++)
	{
		if (*it > *(it + 1))
			std::swap(*it, *(it + 1));
	}

	// Pair elements of each couple to create the sequence to pass to the next recursion
	std::deque<std::pair<T, T> > nextSequence;
	typename std::deque<T>::iterator it;
	for (it = sequence.begin(); it != sequence.end() && it + 1 != sequence.end(); it++)
	{
		nextSequence.push_back(std::make_pair(*it, *(it + 1)));
	}
	// Saving the rest in case of odds elements
	typename std::deque<T>::iterator rest = sequence.end();
	if (it != rest)
		rest = sequence.end() - 1;
	nextSequence = dividePairsAndSort(nextSequence, recursionLevel + 1);

	// Unpairing elements to make the ordered sequence sequence
	std::deque<T> newSequence;
	for (typename std::deque<std::pair<T, T> >::iterator it = nextSequence.begin();
			it != nextSequence.end();
			it++)
	{
		newSequence.push_back(it->first);
		newSequence.push_back(it->second);
	}
	if (rest != sequence.end())
		newSequence.push_back(*rest);
	return newSequence;
}
