#include "Bureaucrat.class.hpp"
#include "ShrubberyCreationForm.class.hpp"
#include "RobotomyRequestForm.class.hpp"
#include "PresidentialPardonForm.class.hpp"
#include "AnsiColorCodes.h"
#include <iostream>

using std::cout;
using std::endl;

// static string header(string const text) {
// 	return ( string( BLK ) + WHTB + text + CRESET );
// }

static void printHeader (
		string const& text,
		string const background = WHTB,
		string const color = BLK,
		std::ostream &os = std::cout) {

    os << string(color) + background + text + CRESET << std::endl;
}

int main(void)
{
	
	printHeader("SECTION 1: ShrubberyCreationForm", BLUB, WHT);
		cout << endl;

	printHeader("Creating a Form:");
		ShrubberyCreationForm	first("BeatifulTree");
		cout << endl;

	printHeader("Creating a copy from the first Form:");
		ShrubberyCreationForm	second(first);
		cout << endl;

	printHeader("Creating some Bureaucrat and sign forms:");
		Bureaucrat high("Mister B.", 1);
		Bureaucrat low("Buscetta", 150);
		cout << endl;
		high.signForm(first);
		low.signForm(second);
		cout << endl;

	printHeader("Printing forms informations:");
		cout << endl;
		printHeader("First", GRNB, WHT);
		cout << first << endl;
		cout << endl;
		printHeader("Copy of first", GRNB, WHT);
		cout << second << endl;
		cout << endl;

	printHeader("Executing some Forms...");
		low.executeForm(first);
		cout << endl;
		high.executeForm(first);
		cout << endl;
		high.executeForm(second);
		cout << endl;

	printHeader("End of the program, automatic calling destructors chain.");

	return 0;
}
