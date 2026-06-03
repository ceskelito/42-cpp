#pragma once

#include <string>
#include <sstream>
#include <cctype>

typedef enum { CHAR, INT, FLOAT, DOUBLE, UNDEFINED, PSEUDO } e_type;

typedef struct s_final {

	e_type		type;
	double		data;
	std::string strRep;

	void	setData(double const &otherData);
	void	setStringRep(bool pseudo = false, std::string literal = "");

}	t_final;

// Type identification functions
bool		isInt(std::string l);
bool		isFloat(std::string l);
bool		isDouble(std::string l);
bool		isPseudo(std::string const &l);
e_type		identify_type(std::string l);

// String literal conversion
template <e_type Type>
std::string getStringLiteral(double const &data);
