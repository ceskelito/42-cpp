#include <deque>
#include <cmath>
#include <algorithm>
#include "Range.hpp"
#include "Element.hpp"
#include "debugUtils.hpp"
#include <iostream>

typedef std::deque<int> dq;
typedef std::deque<Element<dq::iterator> > ElementList;

int g_cmps = 0;

unsigned int	getJacobsthalNumber(unsigned int index) {
	return ( (std::pow(2, index+1) + std::pow(-1, index)) / 3 );
}

void	appendRange(dq &s, Range<dq::iterator> r) {
	s.insert(s.end(), r.first, r.last); 
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
		return (elementSize == 1) ? 1 : elementSize / 2;

	for (dq::iterator it = sequence.begin(); pairSize <= std::distance(it, sequence.end()); it += pairSize) {

		Range<dq::iterator>	firstElement = makeRange(it, it + elementSize - 1);
		Range<dq::iterator>	secondElement = makeRange(it + elementSize, it + pairSize - 1);

		g_cmps++;
		if (*firstElement.last > *secondElement.last)
			std::swap_ranges(firstElement.first, secondElement.first, secondElement.first);
	}
	return divideIntoAndSortPairs(sequence, 2 * elementSize);
}

static void insertPendIntoMain(ElementList &main, ElementList &pend);
static void initializeMainAndPend(dq &sequence, unsigned int elementSize) {
	dq			non;
	ElementList	main, pend;

	// STEP 2: Sort elements in main and pend groups
	int nElements = sequence.size() / elementSize;
	for (int i = 0; i < nElements; i++)
	{
		dq::iterator 			elementStartIt = sequence.begin() + i * elementSize;
		dq::iterator 			elementEndIt = elementStartIt + elementSize;
		Range<dq::iterator>		elementRange = makeRange(elementStartIt,elementEndIt);

		int 					elementIndex = (i / 2) + 1; 
		char 					elementLabel = (i % 2 == 0) ? 'b' : 'a';

		Element<dq::iterator>	element (elementRange, elementLabel, elementIndex);

		if (elementLabel == 'a' || elementIndex == 1)
			main.push_back(element); // Every a's and b1 goes in main
		else
			pend.push_back(element); // Other b's goes in pend
	}

	// Handle remaining units that can't form an element
	unsigned int processedUnits = (sequence.size() / elementSize) * elementSize;
	for (dq::iterator it = sequence.begin() + processedUnits; it != sequence.end(); it++) {
		non.insert(non.end(), *it);
	}

	// DEBUG
	std::cout << "SIZE: " << elementSize << std::endl;

	std::cout << "main : ";
	dq tmpMain;
	for (ElementList::iterator it = main.begin(); it != main.end(); it++)
		appendRange(tmpMain, it->range);
	debug::printDeque(tmpMain);
	std::cout << std::endl;

	std::cout << "pend : ";
	dq tmpPend;
	for (ElementList::iterator it = pend.begin(); it != pend.end(); it++)
		appendRange(tmpPend, it->range);
	debug::printDeque(tmpPend);
	std::cout << std::endl;

	std::cout << "nonp : ";
	debug::printDeque(non);
	std::cout << std::endl << std::endl;
	// END DEBUG

	insertPendIntoMain(main, pend);

	dq reordered;
	for (ElementList::iterator it = main.begin(); it != main.end(); it++)
		appendRange(reordered, it->range);
	reordered.insert(reordered.end(), non.begin(), non.end());
	sequence.swap(reordered);

	if (elementSize > 1)
		initializeMainAndPend(sequence, elementSize / 2);
}

static void insertPendElement(ElementList &main, ElementList &pend, ElementList::iterator &elementToInsert) {

	ElementList::iterator	insertPosition;
	ElementList::iterator	previousPosition;

	for (insertPosition = main.begin(); insertPosition != main.end(); ++insertPosition)
		if (insertPosition->label == 'a' && insertPosition->index == elementToInsert->index)
			break;

	while (insertPosition != main.begin()) {

		previousPosition = insertPosition - 1;

		g_cmps++;
		if (previousPosition->value <= elementToInsert->value)
			break;

		--insertPosition;
	}
	main.insert(insertPosition, *elementToInsert);
	pend.erase(elementToInsert);
}

static void insertPendIntoMain(ElementList &main, ElementList &pend) {

	unsigned int			jacoIndex = 2; // Usefull Jacobsthal numbers starts from 3
	ElementList::iterator	elementToInsert;
	bool					foundJacoNumInPend;

	while (!pend.empty())
	{
		unsigned int	currJacoNum = getJacobsthalNumber(jacoIndex);
		unsigned int	prevJacoNum = getJacobsthalNumber(jacoIndex - 1);

		foundJacoNumInPend = false;

		// Fill main with a batch of pend's elements, from currJacoNum to prevJacoNum
		for (unsigned int pendIndex = currJacoNum; pendIndex > prevJacoNum; --pendIndex)
		{
			// Find the pend element with index corresponding to currJacoNum
			for (elementToInsert = pend.begin(); elementToInsert != pend.end(); ++elementToInsert)
				if (elementToInsert->index == pendIndex)
					break;

			// If the currJacoNum exceed the maximum pend index,
			// break all the cycles and insert pend's element from last to first
			if (elementToInsert == pend.end())
				break;

			// Insert the current element into the main chain
			foundJacoNumInPend = true;
			insertPendElement(main, pend, elementToInsert);
		}

		// Continue breaking all the cycles since currJacoNum was not found in pend's elements indexes
		if (!foundJacoNumInPend)
			break;
		++jacoIndex;
	}

	// Insert the pend's element in the main chain proceding in reverse order
	if (!foundJacoNumInPend) {
		while (!pend.empty())
		{
			elementToInsert = pend.end() - 1;
			insertPendElement(main, pend, elementToInsert);
		}
	}

	pend.clear();
}

std::deque<int> ford_johnson(std::deque<int> sequence) {

	unsigned int elementSize = divideIntoAndSortPairs(sequence);

	// DEBUG
	std::cout << "Diveded And Sorted : ";
	debug::printDeque(sequence);
	std::cout << std::endl;
	// END DEBUG

	initializeMainAndPend(sequence, elementSize);
	return sequence;
}


