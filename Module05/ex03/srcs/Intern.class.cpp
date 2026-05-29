#include "Intern.class.hpp"
#include "ShrubberyCreationForm.class.hpp"
#include "RobotomyRequestForm.class.hpp"
#include "PresidentialPardonForm.class.hpp"
#include <iostream>

using std::cout;
using std::endl;
using std::string;

static string className( void ) {

	const string BLD = "\e[1m";
	const string ITL = "\e[3m";
	const string RST = "\e[0m";

	return (string(BLD) + ITL + "[ RobotomyRequestForm ]" + RST);
}

Intern::Intern( void ) {
	cout << className() << " Constructor called." << endl;
}

Intern::Intern( Intern &other ) {
	(void) other;
	cout << className() << " Copy Constructor called." << endl;
}

Intern& Intern::operator=( Intern &other) {
	(void) other;
	cout << className() << " Assignement operator called." << endl;
	return (*this);
}

Intern::~Intern( void ) {
	cout << className() << " Destructor called." << endl;
}

AForm* Intern::makeForm( string const& form, string const& target) const
{
	static const string names[3] = {
		"robotomy request",
		"presidential pardon",
		"shrubbery creation"
	};

	int name_idx;
	for (name_idx = 0; name_idx < 3 && names[name_idx] != form; ++name_idx) ;

	switch (name_idx) {
		case 0:
			cout << "Intern creates " << form << endl;
			return new RobotomyRequestForm(target);
		case 1:
			cout << "Intern creates " << form << endl;
			return new PresidentialPardonForm(target);
		case 2:
			cout << "Intern creates " << form << endl;
			return new ShrubberyCreationForm(target);
		default:
			cout << "Intern can't find form named " << form << endl;
			return NULL;
	}
}
