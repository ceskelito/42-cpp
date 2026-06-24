#include <ctime>
#include <vector>
#include <algorithm>

// DEBUG
#include <iostream>
using std::cout;
using std::endl;

typedef std::vector<std::pair<int, int> > Couples;

static Couples makeCouples(std::vector<int> sequence) {

	Couples couples;

	std::vector<int>::iterator it = sequence.begin();
	for (; it != sequence.end() && it + 1 != sequence.end(); it += 2) {
		couples.push_back(
			std::make_pair(
				std::max(*it, *(it + 1)),
				std::min(*it, *(it + 1))
			));
	}
	if (sequence.size() % 2 != 0)
		couples.push_back(std::make_pair(-1, (*(sequence.end() - 1))));

	return couples;
}

std::vector<int> ford_johnson(std::vector<int> sequence) {

	if (sequence.size() < 2)
		return sequence;

	std::vector<int>	mainChain;
	Couples				couples = makeCouples(sequence);

	for (Couples::iterator i = couples.begin(); i != couples.end() && i->first >= 0; i++) {
		mainChain.push_back(i->first);
	}
	
	mainChain = ford_johnson(mainChain);
	
	mainChain.insert(mainChain.begin(), couples.begin()->second);	

	// DEBUG
	// Couples::iterator ite = couples.begin();
	// cout << "max min" << endl;
	// for (; ite != couples.end(); ite++)
	// {
	// 	cout << " " << (*ite).first << "   " << (*ite).second << endl;
	// }

	return mainChain;
}

time_t	PmergeMe(std::vector<int> sequence) {
	
	time_t 				time_elapsed = 0; 
	std::vector<int>	sorted; 

	sorted = ford_johnson(sequence);

	//DEBUG
	for (std::vector<int>::iterator it = sorted.begin(); it != sorted.end(); it++)
		cout << *it << " ";
	cout << endl;

	return time_elapsed;
}
