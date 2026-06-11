#include "Span.class.hpp"
#include <iostream>

int main()
{
	Span sp = Span(50000);
	sp.addNumber(1);
	sp.addNumber(4);
	std::cout << sp.shortestSpan() << std::endl;
	std::cout << sp.longestSpan() << std::endl;
	sp.addRange(10000, 999);
	std::cout << sp.shortestSpan() << std::endl;
	std::cout << sp.longestSpan() << std::endl;
	return 0;
}
