#include "ScalarConverter.class.hpp"
#include <iostream>
#include <cstdlib> // Ascii to x conversions

typedef enum { CHAR, INT, FLOAT, DOUBLE, UNDEFINED } e_type;

static bool	isInt( std::string l ) {

	size_t	i = 0;

	if (l[0] == '-') i = 1;

	for (; i < l.length(); i++)
		if (!std::isdigit(l[i])) {
			return false;
		}
	return true;
}

static bool	isFloat( std::string l ) {

	bool		hasDecimal = false;
	std::string	numPart = NULL;
	size_t		i = 0;

	if ( l[l.length() - 1] != 'f' )
		return false;
	if (l[0] == '-')
		i = 1;
	numPart = l.substr(i, l.length() - 1);

	for (; i < numPart.length(); i++) {
		if ( numPart[i] == '.' ) {
			if ( hasDecimal )
				return false;
			hasDecimal = true;
		}
		else if (!std::isdigit(numPart[i]))
			return false;
	}
	return true;
}

static bool isDouble( std::string l ) {

	bool		hasDecimal = false;
	size_t		i = 0;

	if ( l[l.length() - 1] != 'f' )
		return false;
	if (l[0] == '-')
		i = 1;

	for (; i < l.length(); i++) {
		if ( l[i] == '.' ) {
			if ( hasDecimal )
				return false;
			hasDecimal = true;
		}
		else if (!std::isdigit(l[i]))
			return false;
	}
	return true;
}

static e_type identify_type ( std::string l) {

	if ( l.empty() )
		return UNDEFINED;
	else if (l.length() == 1 && std::isalpha(l[0]))
		return CHAR;
	else if ( isInt(l) )
		return INT;
	else if ( isFloat(l) )
		return FLOAT;
	else if ( isDouble(l) )
		return DOUBLE;
	else
		return UNDEFINED;
}

void ScalarConverter::convert( std::string literal) {

	e_type	type = identify_type(literal);
	char	asChar;
	int		asInt;
	float	asFloat;
	double	asDouble;

	// TODO Check the results and manage errors
	switch (type) {
		case CHAR:
		  asChar = literal[0];
		  break;
		case INT:
		  asInt = std::atoi(literal.c_str());
		  break;
		case FLOAT:
		  asFloat = std::atof(literal.c_str());
		  break;
		case DOUBLE:
		  asDouble = std::strtod(literal.c_str(), NULL);
		  break;
		default:
		  break;
	}

	switch (type) {
		case CHAR:
			asInt = static_cast<int> ( asChar );
			asFloat = static_cast<float> ( asChar );
			asDouble = static_cast<double>( asChar );
			break;
		case INT:
			asChar = static_cast<char> ( asInt );
			asFloat = static_cast<float> ( asInt );
			asDouble = static_cast<double>( asInt );
			break;
		case FLOAT:
			asChar = static_cast<char> ( asFloat );
			asInt = static_cast<int> ( asFloat );
			asDouble = static_cast<double>( asFloat );
			break;
		case DOUBLE:
			asChar = static_cast<char> ( asDouble );
			asInt = static_cast<int> ( asDouble );
			asFloat = static_cast<float> ( asDouble );
			break;
		default:
			break;
	}

	std::cout <<
		"char: " << asChar << std::endl <<
		"int: " << asInt << std::endl <<
		"double: " << asDouble << std::endl <<
		"float: " << asFloat << std::endl;
}
