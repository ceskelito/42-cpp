#include "ShrubberyCreationForm.class.hpp"
#include "Bureaucrat.class.hpp"

#include <iostream>
#include <fstream>

using std::cout;
using std::endl;


// Constructors
ShrubberyCreationForm::ShrubberyCreationForm(string target) :
	AForm(target + "-SCF", _gradeToSign, _gradeToExec, false),
	_target(target)
{
	cout << "[ ShrubberyCreationForm ] Constructor called for " << this->AForm::getName() << endl;
};

ShrubberyCreationForm::ShrubberyCreationForm(ShrubberyCreationForm const &other) :
	//AForm("copy_" + other.AForm::getName(), other._gradeToSign, other._gradeToExec, other.AForm::isSigned()),
	AForm(other),
	_target(other._target)
{
	cout << "[ ShrubberyCreationForm ] Copy constructor called for " << this->AForm::getName() << endl;
}

// Destructor
ShrubberyCreationForm::~ShrubberyCreationForm( void ) {
	cout << "[ ShrubberyCreationForm ] Destructor called for "  << this->AForm::getName() << endl;
}

// Methods
void	ShrubberyCreationForm::execute(Bureaucrat const & executor) const {
	//TODO Check the executor grade
	(void) executor;	
	cout << "Executing ShrubberyCreationForm from Bureaucrat `" + executor.getName() + "` on target `" << _target << "`" <<  endl;
    std::ofstream file((_target + "_shrubbery").c_str());

    file << "       _-_       \n";
    file << "      /~~~\\     \n";
    file << "     /~~~~~\\    \n";
    file << "    /~~~~~~~\\   \n";
    file << "   /~~~~~~~~~\\  \n";
    file << "        |||      \n";
    file << "        |||      \n";
}
