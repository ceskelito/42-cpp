#include "ScalarConverter.class.hpp"

int main (int ac, char **av)
{
	if (ac < 2)
		return 1;
	ScalarConverter::convert(av[1]);
}
