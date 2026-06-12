#include "Span.class.hpp"
#include "AnsiColorCodes.h"
#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>

using std::cout;
using std::endl;

static void printHeader (
		std::string const& text,
		std::string const background = WHTB,
		std::string const color = BLK,
		std::ostream &os = std::cout) {

    os << std::string(color) + background + text + CRESET << std::endl << std::endl;
}

int main()
{
	srand (time(NULL));
	// Test 1: Basic operations with small Span
	printHeader("Test 1: Basic operations");
	try {
		Span sp(5);
		cout << "Add numbers: 3, 1, 4, 1, 5" << endl;
		sp.addNumber(3);
		sp.addNumber(1);
		sp.addNumber(4);
		sp.addNumber(1);
		sp.addNumber(5);
		cout << "Shortest Span: " << sp.shortestSpan() << endl;
		cout << "Longest Span: " << sp.longestSpan() << endl;
	}
	catch (std::exception &e) {
		cout << "Error: " << e.what() << endl;
	}

	// Test 2: addRange with count and value
	cout << endl;
	printHeader("Test 2: addRange with count and value");
	try {
		Span sp(10);
		cout << "Add 5 times value 10" << endl;
		sp.addRange(5, 10);
		cout << "Add 5 times value 20" << endl;
		sp.addRange(5, 20);
		cout << "Shortest Span: " << sp.shortestSpan() << endl;
		cout << "Longest Span: " << sp.longestSpan() << endl;
	}
	catch (std::exception &e) {
		cout << "Error: " << e.what() << endl;
	}

	// Test 3: addRange with iterators
	cout << endl;
	printHeader("Test 3: addRange with iterators");
	try {
		std::vector<int> range(3);

		range[0] = 100;
		range[1] = 200;
		range[2] = 300;

		Span sp(5);
		cout << "Add range from vector: 100, 200, 300" << endl;
		sp.addRange(range.begin(), range.end());
		cout << "Add 2 more numbers: 150, 250" << endl;
		sp.addNumber(150);
		sp.addNumber(250);
		cout << "Shortest Span: " << sp.shortestSpan() << endl;
		cout << "Longest Span: " << sp.longestSpan() << endl;
	}
	catch (std::exception &e) {
		cout << "Error: " << e.what() << endl;
	}

	// Test 4: Error - Span full
	cout << endl;
	printHeader("Test 4: Error handling - Span full");
	try {
		Span sp(3);
		cout << "Add 4 numbers to Span of size 3" << endl;
		sp.addNumber(1);
		sp.addNumber(2);
		sp.addNumber(3);
		sp.addNumber(4);
	}
	catch (std::exception &e) {
		cout << BLU << "Expected error: " << e.what() << CRESET << endl;
	}

	// Test 5: Error - Not enough elements for shortestSpan
	cout << endl;
	printHeader("Test 5: Error handling - Not enough elements");
	try {
		Span sp(5);
		cout << "Try to get shortestSpan with only 1 element" << endl;
		sp.addNumber(42);
		sp.shortestSpan();
	}
	catch (std::exception &e) {
		cout << BLU << "Expected error: " << e.what() << CRESET << endl;
	}

	// Test 6: Copy constructor and assignment
	cout << endl;
	printHeader("Test 6: Copy constructor and assignment");
	try {
		Span sp1(5);
		sp1.addNumber(10);
		sp1.addNumber(20);
		sp1.addNumber(30);
		
		Span sp2(sp1);  // Copy constructor
		cout << "Original - Shortest: " << sp1.shortestSpan() << ", Longest: " << sp1.longestSpan() << endl;
		cout << "Copy    - Shortest: " << sp2.shortestSpan() << ", Longest: " << sp2.longestSpan() << endl;
		
		Span sp3(10);
		sp3 = sp1;  // Assignment operator
		cout << "Assigned - Shortest: " << sp3.shortestSpan() << ", Longest: " << sp3.longestSpan() << endl;
	}
	catch (std::exception &e) {
		cout << "Error: " << e.what() << endl;
	}

	// Test 7: Large Span
	cout << endl;
	printHeader("Test 7: Large Span with many elements");
	try {
		Span sp(10000);
		cout << "Add 10000 random numbers" << endl;
		for (int i = 0; i < 10000; i++)
			sp.addNumber(rand() % 100000);
		cout << "Shortest Span: " << sp.shortestSpan() << endl;
		cout << "Longest Span: " << sp.longestSpan() << endl;
	}
	catch (std::exception &e) {
		cout << "Error: " << e.what() << endl;
	}

	return 0;
}
