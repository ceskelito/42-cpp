#pragma once

#include <string>
#include <sstream>
#include <limits.h>

typedef enum { CHAR, INT, FLOAT, DOUBLE, UNDEFINED, PSEUDO } e_type;

// Type identification functions
bool		isInt(std::string l);
bool		isFloat(std::string l);
bool		isDouble(std::string l);
bool		isPseudo(std::string const &l);
e_type		identify_type(std::string l);

// String literal conversion
template <e_type Type>
std::string getStringLiteral(double const &data);

// Template specializations
template <>
inline std::string getStringLiteral<CHAR>(double const &data)
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
inline std::string getStringLiteral<INT>(double const &data)
{
	std::ostringstream	oss;
	int const			value = static_cast<int>(data);

	oss << value;
	return oss.str();
}

template <>
inline std::string getStringLiteral<FLOAT>(double const &data)
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
inline std::string getStringLiteral<DOUBLE>(double const &data)
{
	std::ostringstream	oss;
	double const		value = data;

	oss << value;
	if (value - static_cast<int>(value) == 0)
		oss << ".0";
	return oss.str();
}
