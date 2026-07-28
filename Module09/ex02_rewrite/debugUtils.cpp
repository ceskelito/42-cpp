#include "debugUtils.hpp"

#include <deque>
#include <iostream>
#include <sstream>

void debug::printDeque(std::deque<int> d) {

	for (std::deque<int>::iterator it = d.begin(); it != d.end(); it++)
		std::cout << *it << " ";
}

void debug::printDeque(std::deque<int> d, unsigned int elementSize) {
    unsigned int i = 0;
    unsigned int color = 31;

    for (std::deque<int>::iterator it = d.begin(); it != d.end(); it++) {

		if (i == elementSize) {
			i = 0;
			color++;
		}
        if (color == 37)
            color = 31;

        std::ostringstream oss;
        oss << "\033[0;" << color << "m";
        std::cout << oss.str();
        std::cout << *it << " ";
        i++;
    }
    std::cout << "\033[0;37m";
}
