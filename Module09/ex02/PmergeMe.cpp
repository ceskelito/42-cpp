#include <ctime>
#include <deque>
#include <list>
#include <algorithm>

#include "debugUtils.hpp"

using std::deque;

// DEBUG
#include <iostream>
using std::cout;
using std::endl;

struct Group {
	bool		even;
	deque<int>	chainA;
	deque<int>	chainB;

	Group() : even(false) {}
};

struct Container {
	bool			isCanonical;
	std::deque<int>	sequence;
};

std::deque<bool>	getSplitRule(deque<int> sequence) {

	std::deque<bool> firstBigger;

	for (deque<int>::iterator it = sequence.begin();
			it != sequence.end() && it + 1 != sequence.end();
			it += 2)
		firstBigger.push_back(*it == std::max(*it, *(it + 1)));

	// if (sequence.size() % 2 != 0){
	// 	group.even = true;
	// 	group.chainB.push_back((*(sequence.end() - 1)));
	// }

	return firstBigger;

}

Group	applySplitRule(deque<int> sequence, deque<bool> firstIsBigger) {
	
	Group		group;

	for (deque<int>::iterator it = sequence.begin();
			it != sequence.end() && it + 1 != sequence.end();
			it += 2)
	{
		if (*firstIsBigger.begin()) {
			group.chainA.push_back(*it);
			group.chainB.push_back(*it + 1);
		}
		else {
			group.chainA.push_back(*it + 1);
			group.chainB.push_back(*it);
		}
		firstIsBigger.pop_front();
	}
	if (sequence.size() % 2 != 0){
		group.chainB.push_back((*(sequence.end() - 1)));
	}

	return group;
}

Group	splitPairs(deque<int> sequence) {

	Group		group;

	for (deque<int>::iterator it = sequence.begin();
			it != sequence.end() && it + 1 != sequence.end();
			it += 2)
	{
		group.chainA.push_back(std::max(*it, *(it + 1)));
		group.chainB.push_back(std::min(*it, *(it + 1)));
	}
	if (sequence.size() % 2 != 0){
		group.even = true;
		group.chainB.push_back((*(sequence.end() - 1)));
	}

	return group;
}

std::list<Group>	getGroupsList(Group g) {

	std::list<Group> list;

	if (g.chainA.size() <= 1) {
		list.push_back(g);
		return list;
	}

	static int n_iter = 0;

	cout << "iter n " << ++n_iter << endl;
	cout << "a: "; debug::printDeque(g.chainA); cout << endl;
	cout << "b: "; debug::printDeque(g.chainB); cout << endl;
	cout << endl;

	Group group1 = splitPairs(g.chainA);
	Group group2 = splitPairs(g.chainB);
	std::list<Group> listA = getGroupsList(group1);
	std::list<Group> listB = getGroupsList(group2);
	list.splice(list.end(), listA);
	list.splice(list.end(), listB);

	return list;
}


deque<int>	ford_johnson(deque<int> sequence) {

	deque<int>	sorted;
	std::list<Group> groups = getGroupsList(splitPairs(sequence));

	for (std::list<Group>::iterator it = groups.begin(); it != groups.end(); ++it)
	{
		// cout << "a size: " << it->chainA.size() << endl;
		// cout << "b size: " << it->chainB.size() << endl;
		cout << "a: "; debug::printDeque(it->chainA); cout << endl;
		cout << "b: "; debug::printDeque(it->chainB); cout << endl;
		cout << endl;
	}

	return sorted;
}

time_t	PmergeMe(deque<int> sequence) {
	
	time_t 				time_elapsed = 0; 

	deque<int> sorted = ford_johnson(sequence);
	
	for (deque<int>::iterator it = sorted.begin(); it != sorted.end(); it++)
		cout << *it << " ";
	cout << endl;

	return time_elapsed;
}
