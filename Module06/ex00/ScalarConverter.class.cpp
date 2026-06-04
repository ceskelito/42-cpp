#include "ScalarConverter.class.hpp"
#include "ScalarConverter.utils.hpp"
#include <iostream>
#include <cstdlib>
#include <limits.h>
#include <errno.h>

void ScalarConverter::convert(std::string literal) {

	e_type	typeFound = identify_type(literal);
	double	parsedValue = 0.0;
	bool	isOverflow = false;

	// Parse the input value based on type
	errno = 0;
	switch (typeFound) {
		case CHAR:
			parsedValue = literal[0];
			break;
		case INT:
			parsedValue = std::strtol(literal.c_str(), NULL, 10);
			isOverflow = (parsedValue > INT_MAX || parsedValue < INT_MIN);
			break;
		case FLOAT:
			parsedValue = std::strtof(literal.c_str(), NULL);
			break;
		case DOUBLE:
			parsedValue = std::strtod(literal.c_str(), NULL);
			break;
		case PSEUDO:
			break;
		default:
			break;
	}

	// Output conversions
	if (typeFound < UNDEFINED && !isOverflow && !errno) {
		std::cout << "char: " << getStringLiteral<CHAR>(parsedValue) << std::endl;
		std::cout << "int: " << getStringLiteral<INT>(parsedValue) << std::endl;
		std::cout << "float: " << getStringLiteral<FLOAT>(parsedValue) << std::endl;
		std::cout << "double: " << getStringLiteral<DOUBLE>(parsedValue) << std::endl;
	}
	else if (typeFound == PSEUDO) {
		std::string s = literal.substr(literal.length() - 3, 3);
		if (s == "anf" || s == "nff")
			literal.erase(literal.size() - 1);
		std::cout << "char: impossible" << std::endl;
		std::cout << "int: impossible" << std::endl;
		std::cout << "float: " << literal << "f" << std::endl;
		std::cout << "double: " << literal << std::endl;
	}
	else {
		std::cout << "char: impossible" << std::endl;
		std::cout << "int: impossible" << std::endl;
		std::cout << "float: impossible" << std::endl;
		std::cout << "double: impossible" << std::endl;
	}
}
