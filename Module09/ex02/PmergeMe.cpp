#include <ctime>
#include <vector>
#include <algorithm>

// DEBUG
#include <iostream>
using std::cout;
using std::endl;

typedef std::vector<std::pair<int, int> > Couples;

struct Chain {
	bool				has_orfan = false;
	std::vector<int>	a;
	std::vector<int>	b;
};

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

// static Chain makeChains(std::vector<int> sequence) {
//
// }

std::vector<int> jacobsthalSequence(int n) {
    std::vector<int> sequence;
    if (n < 0) {
        return sequence;
    }

    int a = 0; // J(0)
    int b = 1; // J(1)

    sequence.push_back(a);
    if (n >= 1) {
        sequence.push_back(b);
    }

    while (true) {
        int next = b + 2 * a;
        if (next > n) {
            break;
        }
        sequence.push_back(next);
        a = b;
        b = next;
    }

    return sequence;
}

Couples				ford_johnson(Couples couples);
std::vector<int>	ford_johnson(std::vector<int> sequence) {
	if (sequence.size() < 2)
		return sequence;
	Couples c = ford_johnson(makeCouples(sequence));
	std::vector<int> v;
	for(Couples::iterator it = c.begin(); it != c.end(); it++)
		v.push_back(it->first);
	return v;
}

Couples ford_johnson(Couples couples) {

	if (couples.size() < 2) {
		couples.insert(couples.begin(), std::make_pair(couples[0].second, -1));
		return couples;
	}

	std::vector<int>	mainChain;
	Couples				couples = makeCouples(sequence);

	for (Couples::iterator i = couples.begin(); i != couples.end() && i->first >= 0; i++) {
		mainChain.push_back(i->first);
	}
	
	mainChain = ford_johnson(mainChain);
	
	int i = 0;
	mainChain.insert(mainChain.begin(), couples[i++].second);

	// Maybe obtain jacobsthal groups instead of the sequence ???
	std::vector<int> jacobsthal = jacobsthalSequence(couples.size());
/*
 * 1. hai mainChain con le a ordinate e b₁ in testa 
 * 2. calcola sequenza di Jacobsthal 
 * 3. per ogni gruppo di Jacobsthal:
       per ogni b del gruppo (a ritroso):
           trova la posizione con ricerca binaria nella zona corretta
           inserisci b in quella posizione 
 * 4. se esiste elemento spaiato:
			inseriscilo con ricerca binaria su tutta la mainChain
 */
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
