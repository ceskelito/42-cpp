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
template <e_type Type>
static std::string testToString(void *ptr);

template <>
std::string testToString<CHAR>(void *ptr) {
    std::ostringstream oss;
    char value = *static_cast<char*>(ptr);
    if (!std::isprint(value))
        oss << "not displayable";
    else
        oss << "'" << value << "'";
    return oss.str();
}

template <>
std::string testToString<INT>(void *ptr) {
    std::ostringstream oss;
    int value = *static_cast<int*>(ptr);
    oss << value;
    return oss.str();
}

template <>
std::string testToString<FLOAT>(void *ptr) {
    std::ostringstream oss;
    float value = *static_cast<float*>(ptr);
    oss << value;
    if (value - static_cast<int>(value) == 0)
        oss << ".0";
    oss << "f";
    return oss.str();
}

template <>
std::string testToString<DOUBLE>(void *ptr) {
    std::ostringstream oss;
    double value = *static_cast<double*>(ptr);
    oss << value;
    if (value - static_cast<int>(value) == 0)
        oss << ".0";
    return oss.str();
}

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

// Funzioni wrapper non-template per ogni tipo
void* castToInt(void* ref) {
    return new int(static_cast<int>(*static_cast<int*>(ref)));
}

void* castToFloat(void* ref) {
    return new float(static_cast<float>(*static_cast<float*>(ref)));
}

void* castToDouble(void* ref) {
    return new double(static_cast<double>(*static_cast<double*>(ref)));
}

void* castToChar(void* ref) {
    return new char(static_cast<char>(*static_cast<char*>(ref)));
}

typedef struct s_final {

	e_type		type;
	void		*data = NULL;
	std::string strRep;
	void*		(*cast)(void*);

	std::string toStringValue() const {
        switch (type) {
            case CHAR:
                return testToString<CHAR>(data);
            case INT:
                return testToString<INT>(data);
            case FLOAT:
                return testToString<FLOAT>(data);
            case DOUBLE:
                return testToString<DOUBLE>(data);
            default:
                return "undefined";
        }
    }
} t_final;

#include <limits.h>

void ScalarConverter::convert( std::string literal) {

	e_type	type = identify_type(literal);
	
	char	asChar;
	long int		asInt;
	float	asFloat;
	double	asDouble;

	std::string	strRep[4];

	t_final final[4];
	for ( int i = 0; i < UNDEFINED; i++ )
		final[i].type = static_cast<e_type>(i);
	final[INT].cast = &castToInt;
	final[CHAR].cast = &castToChar;
	final[FLOAT].cast = &castToFloat;
	final[DOUBLE].cast = &castToDouble;


	// TODO 
	// - Check the results and manage errors
	// - Manage pseudo-literals
	errno = 0;
	switch (type) {
		case CHAR:
			final[CHAR].data = &literal[0];void* (*castFunc)(void*);
			break;
		case INT:
			asInt = std::strtol(literal.c_str(), NULL, 10);
			final[INT].data = &asInt;
			if (errno == EINVAL) {
			 // TODO 
			}
			break;
		case FLOAT:
			asFloat = std::strtof(literal.c_str(), NULL);
			final[FLOAT].data = &asFloat;
			if (errno == EINVAL) {
			  // TODO
			}
			break;
		case DOUBLE:
			asDouble = std::strtod(literal.c_str(), NULL);
			final[DOUBLE].data = &asDouble;
		  	if (errno == EINVAL) {
		  	    // TODO
		  	}
		  	break;
		default:
			break;
	}

	if ( type != UNDEFINED) {

		for (int i = 0; i < UNDEFINED; i++) {
			if ( i != type )
				final[i].data = final[i].cast(final[type].data);
			final[i].strRep = final[i].toStringValue();
		}
	}
	else {
		for (int i = 0; i < UNDEFINED; i++) {
			final[i].strRep = "impossible";
		}
	}
	// TODO - Move the inner case in a template function
	// switch (type) {
	// 	case CHAR:
	// 		strRep[CHAR] = toString(asChar);
	// 		asInt = static_cast<int> ( asChar );
	// 		strRep[INT] = toString(asInt);
	// 		asFloat = static_cast<float> ( asChar );
	// 		strRep[FLOAT] = toString(asFloat);
	// 		asDouble = static_cast<double>( asChar );
	// 		strRep[DOUBLE] = toString(asDouble);
	// 		break;
	// 	case INT:
	// 		strRep[INT] = toString(asInt);
	// 		// TODO Isolate this logic into a function. Maybe a template can manage the whole conversion??
	// 		if ( asInt < 0 || asInt > 128 )
	// 			strRep[CHAR] = "impossible";
	// 		else {
	// 			asChar = static_cast<char> ( asInt );
	// 			strRep[CHAR] = toString(asChar);
	// 		} // End of the todo's logic
	// 		asFloat = static_cast<float> ( asInt );
	// 		strRep[FLOAT] = toString(asFloat);
	// 		asDouble = static_cast<double>( asInt );
	// 		strRep[DOUBLE] = toString(asDouble);
	// 		break;
	// 	case FLOAT:
	// 		strRep[FLOAT] = toString(asFloat);
	// 		asChar = static_cast<char> ( asFloat );
	// 		strRep[CHAR] = toString(asChar);
	// 		asInt = static_cast<int> ( asFloat );
	// 		strRep[INT] = toString(asInt);
	// 		asDouble = static_cast<double>( asFloat );
	// 		strRep[DOUBLE] = toString(asDouble);
	// 		break;
	// 	case DOUBLE:
	// 		strRep[DOUBLE] = toString(asDouble);
	// 		asChar = static_cast<char> ( asDouble );
	// 		strRep[CHAR] = toString(asChar);
	// 		asInt = static_cast<int> ( asDouble );
	// 		strRep[INT] = toString(asInt);
	// 		asFloat = static_cast<float> ( asDouble );
	// 		strRep[FLOAT] = toString(asFloat);
	// 		break;
	// 	default:
	// 		for (int i = 0; i < UNDEFINED; i++)
	// 			strRep[i] = "impossible";
	// 		break;
	// }

	std::cout <<
	"char: " << final[CHAR].strRep << std::endl <<
	"int: " << final[INT].strRep<< std::endl <<
	// "int: " << (final[INT].data)) << std::endl <<
	"float: " << final[FLOAT].strRep << std::endl <<
	"double: " << final[DOUBLE].strRep << std::endl;
}
