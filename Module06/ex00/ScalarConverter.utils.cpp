#include "ScalarConverter.utils.hpp"
#include <iostream>
#include <limits.h>

bool isInt(std::string l)
{
	size_t	i = 0;

	if (l[0] == '-')
		i = 1;

	for (; i < l.length(); i++)
		if (!std::isdigit(l[i]))
			return false;
	return true;
}

bool isFloat(std::string l)
{
	bool		hasDecimal = false;
	std::string	numPart;
	size_t		i = 0;

	if (l[l.length() - 1] != 'f')
		return false;
	if (l[0] == '-')
		i = 1;
	numPart = l.substr(i, l.length() - 1);

	for (; i < numPart.length(); i++) {
		if (numPart[i] == '.') {
			if (hasDecimal)
				return false;
			hasDecimal = true;
		}
		else if (!std::isdigit(numPart[i]))
			return false;
	}
	return true;
}

bool isDouble(std::string l)
{
	bool		hasDecimal = false;
	size_t		i = 0;

	if (l[0] == '-')
		i = 1;

	for (; i < l.length(); i++) {
		if (l[i] == '.') {
			if (hasDecimal)
				return false;
			hasDecimal = true;
		}
		else if (!std::isdigit(l[i]))
			return false;
	}
	return true;
}

bool isPseudo(std::string const &l)
{
	if (l == "nan" || l == "+inf" || l == "-inf" || l == "inf" ||
		l == "nanf" || l == "+inff" || l == "-inff" || l == "inff")
		return true;
	return false;
}

e_type identify_type(std::string l)
{
	if (l.empty())
		return UNDEFINED;
	else if (l.length() == 1 && !std::isdigit(l[0]))
		return CHAR;
	else if (isInt(l))
		return INT;
	else if (isFloat(l))
		return FLOAT;
	else if (isDouble(l))
		return DOUBLE;
	else if (isPseudo(l))
		return PSEUDO;
	return UNDEFINED;
}

// Template specializations for getStringLiteral
template <>
std::string getStringLiteral<CHAR>(double const &data)
{
	std::ostringstream	oss;
	char const			value = static_cast<char>(data);

	if (data < CHAR_MIN || data > CHAR_MAX)
		oss << "impossible";
	else if (!std::isprint(data))
		oss << "not displayable";
	else
		oss << "'" << value << "'";
	return oss.str();
}

template <>
std::string getStringLiteral<INT>(double const &data)
{
	std::ostringstream	oss;
	int const			value = static_cast<int>(data);

	oss << value;
	return oss.str();
}

template <>
std::string getStringLiteral<FLOAT>(double const &data)
{
	std::ostringstream	oss;
	float const			value = static_cast<float>(data);

	oss << value;
	if (value - static_cast<int>(value) == 0)
		oss << ".0";
	oss << "f";
	return oss.str();
}

template <>
std::string getStringLiteral<DOUBLE>(double const &data)
{
	std::ostringstream	oss;
	double const		value = data;

	oss << value;
	if (value - static_cast<int>(value) == 0)
		oss << ".0";
	return oss.str();
}

void t_final::setData(double const &otherData)
{
	switch (this->type) {
		case CHAR:
			// this->data = static_cast<char>(otherData);
			this->data = otherData;
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
}

void t_final::setStringRep(bool pseudo, std::string literal)
{
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
}
