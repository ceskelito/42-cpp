#include "ShrubberyCreationForm.class.hpp"
#include <iostream>
#include <fstream>

using std::cout;
using std::endl;

static string className( void ) {

	const string BLD = "\e[1m";
	const string ITL = "\e[3m";
	const string RST = "\e[0m";

	return (string(BLD) + ITL + "[ ShrubberyCreationForm ]" + RST);
}

// Constructors / Destructor
ShrubberyCreationForm::ShrubberyCreationForm(string target) :
	AForm(target + "-SCF", _gradeToSign, _gradeToExec),
	_target(target)
{
	cout << className() << " Constructor called for " << this->AForm::getName() << endl;
};

ShrubberyCreationForm::ShrubberyCreationForm(ShrubberyCreationForm const &other) :
	AForm(other),
	_target(other._target)
{
	cout << className() << " Copy constructor called for " << this->AForm::getName() << endl;
}

ShrubberyCreationForm::~ShrubberyCreationForm( void ) {
	cout << className() << " Destructor called for "  << this->AForm::getName() << endl;
}

// Methods
void	ShrubberyCreationForm::execute(Bureaucrat const & executor) const {
	
	AForm::execute(executor);

    std::ofstream file((_target + "_shrubbery").c_str());

    file << "       _-_       \n";
    file << "      /~~~\\     \n";
    file << "     /~~~~~\\    \n";
    file << "    /~~~~~~~\\   \n";
    file << "   /~~~~~~~~~\\  \n";
    file << "        |||      \n";
    file << "        |||      \n";
}
