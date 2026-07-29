#include <deque>
#include <cmath>
#include <algorithm>
#include "Range.hpp"
#include "Element.hpp"
#include "debugUtils.hpp"

// TODO Modify Range struct to use the [first, last) c++ standard (now using [first, last] )

typedef std::deque<int> dq;

unsigned int	getJacobsthalNumber(unsigned int index) {
	return ( (std::pow(2, index+1) + std::pow(-1, index)) / 3 );
}

void	appendRange(dq &s, Range<dq::iterator> r) {
	s.insert(s.end(), r.first, r.last + 1);
}

/**
 * @param sequence - The original sequence
 * @param elementSize - The initial size of the element
 *
 * Divide the sequence in elements of size elementSize, doubled on every recursion;
 * puts the smaller element of each pair before the bigger element.
 *
 * An element is a range of units in the sequence.
 * The value of the element is determined by the last unit in the element.
 *
 * Break the recursion when the size of the sequence is smaller then the size of a pair.
 *
 * Return value: The latest possible size of the elements
 * 
 * */
static int divideIntoAndSortPairs(dq &sequence, unsigned int elementSize = 1) {

	unsigned int pairSize = 2 * elementSize;

	if (pairSize > sequence.size())
		return elementSize / 2;

	for (dq::iterator it = sequence.begin(); pairSize <= std::distance(it, sequence.end()); it += pairSize) {

		Range<dq::iterator>	firstElement = makeRange(it, it + elementSize - 1);
		Range<dq::iterator>	secondElement = makeRange(it + elementSize, it + pairSize - 1);

		if (*firstElement.last > *secondElement.last)
			std::swap_ranges(firstElement.first, secondElement.first, secondElement.first);
	}
	return divideIntoAndSortPairs(sequence, 2 * elementSize);
}

static void insertPendIntoMain(std::deque<Element<dq::iterator> > &main, std::deque<Element<dq::iterator> > &pend);
static void initializeMainAndPend(dq &sequence, unsigned int elementSize) {
	
	dq non;
	std::deque<Element<dq::iterator> > main, pend;

	unsigned int	pairSize = 2 * elementSize;

	// STEP 2: Sort elements in main and pend groups
	int index = 1;
	for (dq::iterator it = sequence.begin(); pairSize <= std::distance(it, sequence.end()); it += pairSize, index++)
	{
		Element<dq::iterator>	elementB (makeRange(it, it + elementSize - 1), 'b', index);
		Element<dq::iterator>	elementA (makeRange(it + elementSize, it + pairSize - 1), 'a', index);
		
		if (it == sequence.begin()) 
			main.push_back(elementB); // Only b1 goes in main
		else
			pend.push_back(elementB); // Other b's goes in pend
		main.push_back(elementA); // Every a goes in main
	}

	// Handle remaining elements
	unsigned int processedElements = (sequence.size() / pairSize) * pairSize;
	for (dq::iterator it = sequence.begin() + processedElements; it != sequence.end(); it++) {
		non.insert(non.end(), *it);
	}

	insertPendIntoMain(main, pend);

	sequence.clear();
	for (std::deque<Element<dq::iterator> >::iterator it = main.begin(); it != main.end(); it++)
		appendRange(sequence, it->range);
	sequence.insert(sequence.end(), non.begin(), non.end());

	if (elementSize > 1)
		initializeMainAndPend(sequence, elementSize / 2);
}

static void insertPendIntoMain(std::deque<Element<dq::iterator> > &main, std::deque<Element<dq::iterator> > &pend) {

	unsigned int jacoIndex = 1;
	while (!pend.empty())
	{
		unsigned int currentIndex = getJacobsthalNumber(jacoIndex) + 1;
		unsigned int previousIndex = (jacoIndex > 1) ? getJacobsthalNumber(jacoIndex - 1) + 1 : 1;

		for (unsigned int index = currentIndex; index > previousIndex; --index)
		{
			std::deque<Element<dq::iterator> >::iterator elementToInsert;
			std::deque<Element<dq::iterator> >::iterator insertPosition;

			// Find the right pend element
			for (elementToInsert = pend.begin(); elementToInsert != pend.end(); ++elementToInsert)
				if (elementToInsert->index == index)
					break;
			if (elementToInsert == pend.end())
				break; // Manage the case !

			for (insertPosition = main.begin(); insertPosition != main.end(); ++insertPosition)
				if (insertPosition->label == 'a' && insertPosition->index == elementToInsert->index - 1)
					break;
			if (insertPosition == main.end())
				break; // Manage the case !

			while (insertPosition->value > elementToInsert->value)
				insertPosition--;
			main.insert(insertPosition, *elementToInsert);
			pend.erase(elementToInsert);
		}
		++jacoIndex;
	}
	pend.clear();
}

std::deque<int> ford_johnson(std::deque<int> sequence) {
	unsigned int elementSize = divideIntoAndSortPairs(sequence);

	// DEBUG
	std::cout << "Diveded And Sorted : ";
	debug::printDeque(sequence);
	std::cout << std::endl;

	initializeMainAndPend(sequence, elementSize);
	return sequence;
}


