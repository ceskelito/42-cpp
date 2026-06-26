#include <ctime>
#include <deque>
#include <list>
#include <algorithm>

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

Group	getGroup(deque<int> sequence) {

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

std::list<Group>	makeGroupsList(Group g) {

	std::list<Group> list;
	list.push_back(g);

	if (g.chainA.size() <= 1) {
		return list;
	}

	Group grA = getGroup(g.chainA);
	Group grB = getGroup(g.chainB);
	std::list<Group> listA = makeGroupsList(grA);
	std::list<Group> listB = makeGroupsList(grB);
	list.splice(list.end(), listA);
	list.splice(list.end(), listB);

	return list;
}

deque<int>	ford_johnson(deque<int> sequence) {

	deque<int>	sorted;
	std::list<Group> groups = makeGroupsList(getGroup(sequence));

	for (std::list<Group>::iterator it = groups.begin(); it != groups.end(); ++it)
	{
		cout << "a size: " << it->chainA.size() << endl;
		cout << "b size: " << it->chainB.size() << endl;
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
