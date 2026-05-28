#include "RobotomyRequestForm.class.hpp"
#include <iostream>
#include <cstdlib> // Needed for rand() and srand()
#include <ctime>   // Needed for time()
using std::cout;
using std::endl;

static string className( void ) {

	const string BLD = "\e[1m";
	const string ITL = "\e[3m";
	const string RST = "\e[0m";

	return (string(BLD) + ITL + "[ RobotomyRequestForm ]" + RST);
}

// Constructors / Destructor
RobotomyRequestForm::RobotomyRequestForm(string target) :
	AForm(target + "-RRT", _gradeToSign, _gradeToExec),
	_target(target)
{
	cout << className() << " Constructor called for " << this->AForm::getName() << endl;
};

RobotomyRequestForm::RobotomyRequestForm(RobotomyRequestForm const &other) :
	AForm(other),
	_target(other._target)
{
	cout << className() << " Copy constructor called for " << this->AForm::getName() << endl;
}

RobotomyRequestForm::~RobotomyRequestForm( void ) {
	cout << className() << " Destructor called for "  << this->AForm::getName() << endl;
}

// Methods
void	RobotomyRequestForm::execute(Bureaucrat const & executor) const {
	
		AForm::execute(executor);
		srand(time(0));
		cout << "*#+ DriLliNg NOiSeS #*#" << endl;
		if (rand() % 2)
			cout << _target << " has been robotomized successfully" << endl;
		else
			cout << "Robotomy failed. " << _target << " has not been robotomized." << endl;

}
