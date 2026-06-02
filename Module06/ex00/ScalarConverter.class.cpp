#include "ScalarConverter.class.hpp"
#include <iostream>
#include <cstdlib> // Ascii to x conversions
#include <errno.h>
#include <sstream>
#include <limits.h>

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

// TODO manage the point at the very end
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

// TODO manage the point at the very end
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

template <e_type Type>
static std::string toString(void *data);

template <>
std::string toString<CHAR>(void *data) {

    std::ostringstream	oss;
	int					value = *static_cast<int*>(data);

	if ( value < 0 || value > 127 )
		oss << "impossible";
	else if (!std::isprint(value))
		oss << "not displayable";
	else
		oss << "'" << static_cast<char>(value) << "'";
    return oss.str();
}

template <>
std::string toString<INT>(void *data) {

    std::ostringstream	oss;
    int					value = *static_cast<int*>(data);

    oss << value;
    return oss.str();
}

template <>
std::string toString<FLOAT>(void *data) {

    std::ostringstream	oss;
    float				value = *static_cast<float*>(data);

    oss << value;
    if (value - static_cast<int>(value) == 0)
        oss << ".0";
    oss << "f";
    return oss.str();
}

template <>
std::string toString<DOUBLE>(void *data) {
    std::ostringstream oss;
    double value = *static_cast<double*>(data);
    oss << value;
    if (value - static_cast<int>(value) == 0)
        oss << ".0";
    return oss.str();
}

// template <typename T>
// static std::string toString(const T& value) {
//     std::ostringstream oss;
//     oss << value;
//     return oss.str();
// }
//
// template <>
// std::string toString<float>(const float& value) {
//     std::ostringstream oss;
//     oss << value;
// 	if (value - static_cast<int> ( value ) == 0)
// 		oss << ".0";
// 	oss << "f";
//     return oss.str();
// }
//
// template <>
// std::string toString<double>(const double& value) {
//     std::ostringstream oss;
//     oss << value;
// 	if (value - static_cast<int> ( value ) == 0)
// 		oss << ".0";
//     return oss.str();
// }
//
// template <>
// std::string toString<char>(const char& value) {
//     std::ostringstream oss;
// 	if (!std::isprint(value))
// 		oss << "not displayable";
// 	else
// 		oss << "'" << value << "'";
//     return oss.str();
// }
//

// Helper function to extract value as double from any type
static double getDoubleValue(e_type type, void *ref) {
    switch(type) {
        case CHAR: return static_cast<double>(*static_cast<char*>(ref));
        case INT: return static_cast<double>(*static_cast<int*>(ref));
        case FLOAT: return static_cast<double>(*static_cast<float*>(ref));
        case DOUBLE: return *static_cast<double*>(ref);
        default: return 0.0;
    }
}

template <e_type Type>
static void*	cast(e_type srcType, void *ref);

template<>
void	*cast<CHAR>(e_type srcType, void *ref) {
    return new char(static_cast<char>(getDoubleValue(srcType, ref)));
}

template<>
void*	cast<INT>(e_type srcType, void* ref) {
    return new int(static_cast<int>(getDoubleValue(srcType, ref)));
}

template<>
void*	cast<FLOAT>(e_type srcType, void* ref) {
    return new float(static_cast<float>(getDoubleValue(srcType, ref)));
}
template<>
void*	cast<DOUBLE>(e_type srcType, void* ref) {
    return new double(getDoubleValue(srcType, ref));
}

typedef struct s_final {

	e_type		type;
	void		*data;
	std::string strRep;

	void*	castValue(e_type srcType, void *ref) const {
		switch (type) {
			case CHAR:
				return cast<CHAR>(srcType, ref);
			case INT:
				return cast<INT>(srcType, ref);
			case FLOAT:
				return cast<FLOAT>(srcType, ref);
			case DOUBLE:
				return cast<DOUBLE>(srcType, ref);
			default:
				return ( NULL );
		}
	};

	std::string toStringValue() const {
        switch (type) {
            case CHAR:
                return toString<CHAR>(data);
            case INT:
                return toString<INT>(data);
            case FLOAT:
                return toString<FLOAT>(data);
            case DOUBLE:
                return toString<DOUBLE>(data);
            default:
                return "undefined";
        }
    }
}	t_final;

void ScalarConverter::convert( std::string literal) {

	e_type		typeFound = identify_type(literal);
	
	long int	asLong;
	float		asFloat;
	double		asDouble;
	t_final		final[4];

	for ( int i = 0; i < UNDEFINED; i++ )
		final[i].type = static_cast<e_type>(i);

	// TODO 
	// - Check the results and manage errors
	// - Manage pseudo-literals
	errno = 0;
	switch (typeFound) {
		case CHAR:
			final[CHAR].data = new char(literal[0]);
			break;
		case INT:
			asLong = std::strtol(literal.c_str(), NULL, 10);
			if ( asLong > INT_MAX || asLong < INT_MIN ) {
				errno = 1;
				break;
			}
			final[INT].data = new int(asLong);
			break;
		case FLOAT:
			asFloat = std::strtof(literal.c_str(), NULL);
			final[FLOAT].data = new float(asFloat);
			break;
		case DOUBLE:
			asDouble = std::strtod(literal.c_str(), NULL);
			final[DOUBLE].data = new double(asDouble);
		  	break;
		default:
			break;
	}

	if ( errno || typeFound == UNDEFINED) {
		for (int i = 0; i < UNDEFINED; i++) {
			final[i].strRep = "impossible";
		}
	}
	else {
		for (int i = 0; i < UNDEFINED; i++) {
			if ( i != typeFound )
				final[i].data = final[i].castValue(typeFound, final[typeFound].data);
			final[i].strRep = final[i].toStringValue();
		}
	}

	std::cout <<
	"char: " << final[CHAR].strRep << std::endl <<
	"int: " << final[INT].strRep<< std::endl <<
	// "int: " << (final[INT].data)) << std::endl <<
	"float: " << final[FLOAT].strRep << std::endl <<
	"double: " << final[DOUBLE].strRep << std::endl;
}
