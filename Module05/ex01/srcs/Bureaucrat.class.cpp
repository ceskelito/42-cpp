#include "Bureaucrat.class.hpp"
#include <iostream>

using std::string;
using std::cout;
using std::endl;

//	Constructors
Bureaucrat::Bureaucrat(void): _name("BobTheChairHeater"), _grade(MinGrade) {
	cout << "Bureaucrat Default Constructor called for " << _name << " with grade of " << _grade << endl;
}

Bureaucrat::Bureaucrat( string const name, int grade): _name(name) {
	cout << "Bureaucrat Constructor called for " << _name << " with grade of " << grade << endl;

	_setGrade(grade);
};

Bureaucrat::Bureaucrat( const Bureaucrat &other): _name(other._name + "_copy"), _grade(other._grade) {
	cout << "Bureaucrat Copy Constructor called to copy " << other._name << " into " << _name << 
		" with grade of " << _grade << endl;
};

//	Deconstructor
Bureaucrat::~Bureaucrat() {
	std::cout << "Bureaucrat Deconstructor for " << this->getName() << " called" << std::endl;
}

// Overloaded Operators
Bureaucrat &Bureaucrat::operator=(const Bureaucrat &other) {
	if (this != &other)
	{
		_grade = other._grade;
	}

	return *this;
}

//	Stream Operators
std::ostream	&operator<<(std::ostream &o, const Bureaucrat &b) {
	o << b.getName() << ", bureaucrat grade " << b.getGrade();
	return o;
}

//	Getter
string	Bureaucrat::getName( void ) const {
	return _name;
}

int		Bureaucrat::getGrade( void ) const {
	return _grade;
}

//	Setter
void	Bureaucrat::_setGrade(int grade) {
	if (grade < MaxGrade)
		throw GradeTooHighException();
	else if (grade > MinGrade)
		throw GradeTooLowException();
	_grade = grade;
}

// Public Methods
void	Bureaucrat::incrementGrade( void ) {
	cout << "Attempting to increment grade of Bureaucrat " << _name << endl;
	_setGrade(_grade - 1);
}

void	Bureaucrat::decrementGrade( void ) {
	cout << "Attempting to decrement grade of Bureaucrat " << _name << endl;
	_setGrade(_grade + 1);
}

void	Bureaucrat::signForm( Form &f ) const {
	
	try
	{
		f.beSigned(*this);
	}
	catch (Form::GradeTooLowException &e)
	{
		cout << _name << " couldn't sign " << f.getName() << " because grade too low.";
		return;
	}
	cout << _name << " signed " << f.getName();
}

//	Execptions
const char *Bureaucrat::GradeTooHighException::what( void ) const throw() {
	return "Attempting to assign a grade higher than the maximus (1).";
}

const char *Bureaucrat::GradeTooLowException::what( void ) const throw() {
	return "Attempting to assign a grade lower than the minus (150).";
}
