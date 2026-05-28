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

void ShrubberyCreationRoutine( void )
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

	return;
}

void RobotomyRequestRoutine( void )
{	
	printHeader("SECTION 2: RobotomyRequestForm", REDB, WHT);
		cout << endl;

	printHeader("Creating a Form:");
		RobotomyRequestForm	first("Target Subject");
		cout << endl;

	printHeader("Creating a copy from the first Form:");
		RobotomyRequestForm	second(first);
		cout << endl;

	printHeader("Creating some Bureaucrat and sign forms:");
		Bureaucrat high("Colonel", 72);
		Bureaucrat low("Private", 100);
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

	return;
}

void PresidentialPardonRoutine( void )
{	
	printHeader("SECTION 3: PresidentialPardonForm", YELB, BLK);
		cout << endl;

	printHeader("Creating a Form:");
		PresidentialPardonForm	first("Criminal");
		cout << endl;

	printHeader("Creating a copy from the first Form:");
		PresidentialPardonForm	second(first);
		cout << endl;

	printHeader("Creating some Bureaucrat and sign forms:");
		Bureaucrat highestRank("President", 5);
		Bureaucrat lowRank("Officer", 50);
		cout << endl;
		highestRank.signForm(first);
		lowRank.signForm(second);
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
		lowRank.executeForm(first);
		cout << endl;
		highestRank.executeForm(first);
		cout << endl;
		highestRank.executeForm(second);
		cout << endl;

	return;
}

int main(void)
{
	
	ShrubberyCreationRoutine();
	cout << endl << endl;
	RobotomyRequestRoutine();
	cout << endl << endl;
	PresidentialPardonRoutine();

	printHeader("End of the program, automatic calling destructors chain.");

	return 0;
}
