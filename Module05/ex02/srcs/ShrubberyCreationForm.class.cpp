#include "ShrubberyCreationForm.class.hpp"

#include <iostream>

using std::cout;
using std::endl;


// Constructors
ShrubberyCreationForm::ShrubberyCreationForm(string target) :
	AForm(target + "_ShrubberyCreationForm", _gradeToSign, _gradeToExec, false),
	_target(target)
{
	cout << "Constructor called for " << this->AForm::getName() << endl;
};

ShrubberyCreationForm::ShrubberyCreationForm(ShrubberyCreationForm const &other) :
	AForm("copy_" + other.AForm::getName(), other._gradeToSign, other._gradeToExec, other.AForm::isSigned()),
	_target(other._target)
{
	cout << "Copy constructor called for " << this->AForm::getName() << endl;
}

// Destructor
ShrubberyCreationForm::~ShrubberyCreationForm( void ) {
	cout << "Destructor called for "  << this->AForm::getName() << endl;
}

// Methods
void	ShrubberyCreationForm::execute(Bureaucrat const & executor) const {
	//TODO implement the real function
	(void) executor;	
	cout << "Executing ShrubberyCreationForm on " << _target << endl;
}
