#include "Span.class.hpp"
#include "AnsiColorCodes.h"
#include <iostream>
#include <string>

using std::cout;
using std::endl;

static void printHeader (
		std::string const& text,
		std::string const background = WHTB,
		std::string const color = BLK,
		std::ostream &os = std::cout) {

    os << std::string(color) + background + text + CRESET << std::endl;
}

int main()
{
	Span	sp10u(10);
	Span	sp50k(50 * 1000);

	printHeader("Span of size 10");
	try {
		cout << "Add numbers: 1, 4, 8" << endl;
		sp10u.addNumber(1);
		sp10u.addNumber(4);
		sp10u.addNumber(8);
		cout << "Shortest Span: " << sp10u.shortestSpan() << endl;
		cout << "Longest Span: " << sp10u.longestSpan() << endl;
		cout << "Add 10 times the number 15" << endl;
		sp10u.addRange(10, 15);
	}
	catch (std::length_error &e) {
		cout << "Error: " << e.what() << endl;
	}
	
	sp10u.addRange(10000, 999);
	std::cout << sp10u.shortestSpan() << std::endl;
	std::cout << sp10u.longestSpan() << std::endl;
	return 0;
}
