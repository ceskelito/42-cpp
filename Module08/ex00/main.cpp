#include "easyfind.hpp"
#include <vector>
#include <iostream>

using std::cout;
using std::endl;

int main(void) {

	std::vector<int>			v;
	std::vector<int>::iterator	it;

	// Filling vector v
	for (int i = 0; i <= 9; i++)
		v.push_back(i);

	// Printing v
	cout << "Vector: ";
	for ( long unsigned i = 0; i < v.size(); i++ )
		cout << v.at(i) << ' ';
	cout << endl;

	// Finding a legal value
	cout << "Finding a legal value (9): ";

	it = easyfind(v, 9);

	if (it == v.end())
		cout << "nope" << endl;
	else 
		cout << "daje" << endl;

	// Finding an erroneus value
	cout << "Finding an erroneus value (15): ";

	it = easyfind(v, 15);

	if (it == v.end())
		cout << "nope" << endl;
	else 
		cout << "daje" << endl;
}
