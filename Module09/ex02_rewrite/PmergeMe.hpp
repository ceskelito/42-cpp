#include <deque>

// std::deque<int> dividePairsAndSort(std::deque<int> sequence);

std::deque<int> ford_johnson(std::deque<int> sequence);
std::deque<int> ford_johnson_with_count(std::deque<int> sequence, unsigned long &outComparisons);
