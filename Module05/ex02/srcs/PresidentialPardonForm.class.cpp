#include "PresidentialPardonForm.class.hpp"
#include <iostream>

using std::cout;
using std::endl;

static string className( void ) {

	const string BLD = "\e[1m";
	const string ITL = "\e[3m";
	const string RST = "\e[0m";

	return (string(BLD) + ITL + "[ PresidentialPardonForm ]" + RST);
}

// Constructors / Destructor
PresidentialPardonForm::PresidentialPardonForm(string target) :
	AForm(target + "-PPF", _gradeToSign, _gradeToExec),
	_target(target)
{
	cout << className() << " Constructor called for " << this->AForm::getName() << endl;
};

PresidentialPardonForm::PresidentialPardonForm(PresidentialPardonForm const &other) :
	AForm(other),
	_target(other._target)
{
	cout << className() << " Copy constructor called for " << this->AForm::getName() << endl;
}

PresidentialPardonForm::~PresidentialPardonForm( void ) {
	cout << className() << " Destructor called for "  << this->AForm::getName() << endl;
}

// Methods
void	PresidentialPardonForm::execute(Bureaucrat const & executor) const {
	
		AForm::execute(executor);
		cout << _target << " has been pardoned by Zaphod Beeblebrox." << endl;
}
