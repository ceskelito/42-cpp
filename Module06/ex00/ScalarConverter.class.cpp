#include "ScalarConverter.class.hpp"
#include <iostream>
#include <cstdlib> // Ascii to x conversions
#include <errno.h>

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
	std::string	numPart;
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

#include <sstream>
template <typename T>
static std::string toString(const T& value) {
    std::ostringstream oss;
    oss << value;
    return oss.str();
}

template <>
std::string toString<float>(const float& value) {
    std::ostringstream oss;
    oss << value;
	if (value - static_cast<int> ( value ) == 0)
		oss << ".0";
	oss << "f";
    return oss.str();
}

template <>
std::string toString<double>(const double& value) {
    std::ostringstream oss;
    oss << value;
	if (value - static_cast<int> ( value ) == 0)
		oss << ".0";
    return oss.str();
}

template <>
std::string toString<char>(const char& value) {
    std::ostringstream oss;
	if (!std::isprint(value))
		oss << "not displayable";
	else
		oss << "'" << value << "'";
    return oss.str();
}

void ScalarConverter::convert( std::string literal) {

	e_type	type = identify_type(literal);
	
	char	asChar;
	int		asInt;
	float	asFloat;
	double	asDouble;

	std::string	strRep[4];

	// TODO 
	// - Check the results and manage errors
	// - Manage pseudo-literals
	switch (type) {
		case CHAR:
		  asChar = literal[0];
		  break;
		case INT:
		  asInt = std::strtol(literal.c_str(), NULL, 10);
		  if (errno == EINVAL) {
			 // TODO 
		  }
		  break;
		case FLOAT:
		  asFloat = std::strtof(literal.c_str(), NULL);
		  if (errno == EINVAL) {
			  // TODO
		  }
		  break;
		case DOUBLE:
		  asDouble = std::strtod(literal.c_str(), NULL);
		  if (errno == EINVAL) {
			  // TODO
		  }
		  break;
		default:
		  break;
	}

	// TODO - Move the inner case in a template function
	switch (type) {
		case CHAR:
			strRep[CHAR] = toString(asChar);
			asInt = static_cast<int> ( asChar );
			strRep[INT] = toString(asInt);
			asFloat = static_cast<float> ( asChar );
			strRep[FLOAT] = toString(asFloat);
			asDouble = static_cast<double>( asChar );
			strRep[DOUBLE] = toString(asDouble);
			break;
		case INT:
			strRep[INT] = toString(asInt);
			// TODO Isolate this logic into a function. Maybe a template can manage the whole conversion??
			if ( asInt < 0 || asInt > 128 )
				strRep[CHAR] = "impossible";
			else {
				asChar = static_cast<char> ( asInt );
				strRep[CHAR] = toString(asChar);
			} // End of the todo's logic
			asFloat = static_cast<float> ( asInt );
			strRep[FLOAT] = toString(asFloat);
			asDouble = static_cast<double>( asInt );
			strRep[DOUBLE] = toString(asDouble);
			break;
		case FLOAT:
			strRep[FLOAT] = toString(asFloat);
			asChar = static_cast<char> ( asFloat );
			strRep[CHAR] = toString(asChar);
			asInt = static_cast<int> ( asFloat );
			strRep[INT] = toString(asInt);
			asDouble = static_cast<double>( asFloat );
			strRep[DOUBLE] = toString(asDouble);
			break;
		case DOUBLE:
			strRep[DOUBLE] = toString(asDouble);
			asChar = static_cast<char> ( asDouble );
			strRep[CHAR] = toString(asChar);
			asInt = static_cast<int> ( asDouble );
			strRep[INT] = toString(asInt);
			asFloat = static_cast<float> ( asDouble );
			strRep[FLOAT] = toString(asFloat);
			break;
		default:
			for (int i = 0; i < UNDEFINED; i++)
				strRep[i] = "impossible";
			break;
	}

	// std::cout <<
	// 	"char: " << '\'' << asChar << '\'' << std::endl <<
	// 	"int: " << asInt << std::endl <<
	// 	"float: " << asFloat << 'f' << std::endl <<
	// 	"double: " << asDouble << std::endl;
	std::cout <<
		"char: " << strRep[CHAR] << std::endl <<
		"int: " << strRep[INT] << std::endl <<
		"float: " << strRep[FLOAT] << std::endl <<
		"double: " << strRep[DOUBLE] << std::endl;
}
