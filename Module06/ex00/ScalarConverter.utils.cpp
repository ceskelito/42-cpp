#include "ScalarConverter.utils.hpp"

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
