#include "PmergeMe.hpp"
#include <cmath>

int	PmergeMe::_jacobsthal_number(int index)
{
    return ( (std::pow(2, index+1) + std::pow(-1, index)) / 3 );
}