#include "ScalarConverter.class.hpp"
#include "ScalarConverter.utils.hpp"
#include <iostream>
#include <cstdlib>
#include <errno.h>
#include <limits.h>

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
