#include "Bureaucrat.class.hpp"
#include "ShrubberyCreationForm.class.hpp"
#include "AnsiColorCodes.h"
#include <iostream>

using std::cout;
using std::endl;

static string header(string const text) {
	return ( string( BLK ) + WHTB + text + CRESET );
}

int main(void)
{
	cout << header("Creating a Form:") <<  endl;
	ShrubberyCreationForm	first("BeatifulTree");
	cout << endl;

	cout << header("Creating a copy from the first Form:") << endl;
	ShrubberyCreationForm	second(first);
	cout << endl;

	cout << header("Creating a Bureaucrat:") << endl;
	Bureaucrat				b("Bobby", 10);
	cout << endl;

	cout << header("Executing some Forms...") << endl;
	first.execute(b);

	cout << endl;
	cout << header("End of the program, automatic calling destructors chain.") << endl;
	return 0;
}
