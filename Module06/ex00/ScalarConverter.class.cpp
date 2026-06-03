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
	if ( l == "nan" || l == "+inf" || l == "-inf" || l == "inf" ||	
		l == "nanf" || l == "+inff" || l == "-inff" || l == "inff" )
		return true;
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
std::string	getStringLiteral<CHAR>(double const &data) {
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

	void	setStringRep(bool pseudo = false, std::string literal = 0) {

        switch (type) {
            case CHAR:
				if (pseudo)
					this->strRep = "impossible";
				else
					this->strRep = getStringLiteral<CHAR>(data);
				break;
            case INT:
				if (pseudo)
					this->strRep = "impossible";
				else
					this->strRep = getStringLiteral<INT>(data);
				break;
            case FLOAT:
				if (pseudo)
					this->strRep = literal + "f";
				else
					this->strRep = getStringLiteral<FLOAT>(data);
				break;
            case DOUBLE:
				if (pseudo)
					this->strRep = literal;
				else
					this->strRep = getStringLiteral<DOUBLE>(data);
				break;
            default:
                this->strRep = "undefined";
				break;
        }
    };

}	t_final;

void ScalarConverter::convert( std::string literal) {

	t_final		types[4];
	e_type		typeFound = identify_type(literal);

	for ( int i = 0; i < UNDEFINED; i++ )
		types[i].type = static_cast<e_type>(i);

	// TODO 
	// - Manage edge cases like void strings or ' ' character

	// Set the value of the type corresponing with @literal
	errno = 0;
	switch (typeFound) {
		case CHAR:
			types[CHAR].data = literal[0];
			break;
		case INT:
			types[INT].data = std::strtol(literal.c_str(), NULL, 10);
			errno = ( types[INT].data > INT_MAX || types[INT].data < INT_MIN );
			break;
		case FLOAT:
			types[FLOAT].data = std::strtof(literal.c_str(), NULL);
			break;
		case DOUBLE:
			types[DOUBLE].data = std::strtod(literal.c_str(), NULL);
		  	break;
		case PSEUDO:
			break;
		default:
			break;
	}

	
	/* Setting the others data and string representations */
	if ( typeFound < UNDEFINED && !errno ) {
		for (int i = 0; i < UNDEFINED; i++) {
			if ( i != typeFound )
				types[i].setData(types[typeFound].data);
			types[i].setStringRep();
		}
	}
	else if ( typeFound == PSEUDO ) {
		std::string	const	s = literal.substr(literal.length() - 3, 3);

		if (s == "anf" || s == "nff")
			literal.erase(literal.size() - 1);
		for (int i = 0; i < UNDEFINED; i++)
			types[i].setStringRep(true, literal);
	}
	else {
		for (int i = 0; i < UNDEFINED; i++)
			types[i].strRep = "impossible";
	}

	std::cout <<
	"char: " << types[CHAR].strRep << std::endl <<
	"int: " << types[INT].strRep<< std::endl <<
	"float: " << types[FLOAT].strRep << std::endl <<
	"double: " << types[DOUBLE].strRep << std::endl;
}
