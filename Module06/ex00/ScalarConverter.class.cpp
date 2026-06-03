#include "ScalarConverter.class.hpp"
#include <iostream>
#include <cstdlib> // Ascii to x conversions
#include <errno.h>
#include <sstream>
#include <limits.h>

typedef enum { CHAR, INT, FLOAT, DOUBLE, UNDEFINED, PSEUDO } e_type;

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

bool testPseudoLiterals( std::string const &l )
{
	if ( l == "nan" || l == "+inf" || l == "-inf" || l == "inf" )
	{
		std::cout <<
		"char: " << "impossible" << std::endl <<
		"int: " << "impossible" << std::endl <<
		"float: " << l + "f" << std::endl <<
		"double: " << l << std::endl;
		return true;
	}
	else if ( l == "nanf" || l == "+inff" || l == "-inff" || l == "inff" )
	{
		std::cout <<
		"char: " << "impossible" << std::endl <<
		"int: " << "impossible" << std::endl <<
		"float: " << l << std::endl <<
		"double: " << l.substr(0, l.length() - 1) << std::endl;
		return true;
	}
	return false;

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
	else if ( testPseudoLiterals(l) )
		return PSEUDO;
	return UNDEFINED;
}

template <e_type Type>
static std::string getStringLiteral(double const &data);

template <>
std::string getStringLiteral<CHAR>(double const &data) {
    std::ostringstream	oss;
	char const			value = static_cast<char>(data);

	if ( data < CHAR_MIN || data > CHAR_MAX )
		oss << "impossible";
	else if (!std::isprint(data))
		oss << "not displayable";
	else
		oss << "'" << value << "'";
    return oss.str();
}

template <>
std::string getStringLiteral<INT>(double const &data) {
    std::ostringstream	oss;
	int const			value = static_cast<int>(data);

    oss << value;
    return oss.str();
}

template <>
std::string getStringLiteral<FLOAT>(double const &data) {
    std::ostringstream	oss;
    float const			value = static_cast<float>(data);

    oss << value;
    if (value - static_cast<int>(value) == 0)
        oss << ".0";
    oss << "f";
    return oss.str();
}

template <>
std::string getStringLiteral<DOUBLE>(double const &data) {
    std::ostringstream	oss;
    double const		value = data;

    oss << value;
    if (value - static_cast<int>(value) == 0)
        oss << ".0";
    return oss.str();
}

typedef struct s_final {

	e_type		type;
	double		data; // Using a double since is the biggest type possible (between int, char, float and double)
	std::string strRep;

	void	setData(double const &otherData) {
		switch (this->type) {
			case CHAR:
				this->data = static_cast<char>(otherData);
				break;
			case INT:
				this->data = static_cast<int>(otherData);
				break;
			case FLOAT:
				this->data = static_cast<float>(otherData);
				break;
			case DOUBLE:
				this->data = otherData;
				break;
			default:
				this->data = 0.0;
				break;
		}
	};

	std::string toString() const {
        switch (type) {
            case CHAR:
                return getStringLiteral<CHAR>(data);
            case INT:
                return getStringLiteral<INT>(data);
            case FLOAT:
                return getStringLiteral<FLOAT>(data);
            case DOUBLE:
                return getStringLiteral<DOUBLE>(data);
            default:
                return "undefined";
        }
    }
}	t_final;

void ScalarConverter::convert( std::string literal) {

	e_type		typeFound = identify_type(literal);
	
	t_final		final[4];

	for ( int i = 0; i < UNDEFINED; i++ )
		final[i].type = static_cast<e_type>(i);

	// TODO 
	// - Check the results and manage errors
	// - Manage pseudo-literals
	// - Manage edge cases like void strings or ' ' character
	errno = 0;
	switch (typeFound) {
		case CHAR:
			final[CHAR].data = literal[0];
			break;
		case INT:
			final[INT].data = std::strtol(literal.c_str(), NULL, 10);
			errno = ( final[INT].data > INT_MAX || final[INT].data < INT_MIN );
			break;
		case FLOAT:
			final[FLOAT].data = std::strtof(literal.c_str(), NULL);
			break;
		case DOUBLE:
			final[DOUBLE].data = std::strtod(literal.c_str(), NULL);
		  	break;
		case PSEUDO:
			return;
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
				final[i].setData(final[typeFound].data);
			final[i].strRep = final[i].toString();
		}
	}

	std::cout <<
	"char: " << final[CHAR].strRep << std::endl <<
	"int: " << final[INT].strRep<< std::endl <<
	"float: " << final[FLOAT].strRep << std::endl <<
	"double: " << final[DOUBLE].strRep << std::endl;
}
