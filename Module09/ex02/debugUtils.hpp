#pragma once

#include <deque>
#include <iostream>

namespace debug {

void printDeque(std::deque<int> d) {

	for (std::deque<int>::iterator it = d.begin(); it != d.end(); it++)
		std::cout << *it << " ";
}

};
