#include "Form.class.hpp"
#include "Bureaucrat.class.hpp"

#include <iostream>
#include <ostream>

using std::string;
using std::cout;
using std::endl;

//	Constructors
Form::Form(void): _name("GenericForm"), _gradeToSign(MinGrade), _gradeToExec(MinGrade), _signed(false) {
	cout << "Form Default Constructor called for " << _name << " with grades required (sign/exec): "
		<< _gradeToSign << "/" << _gradeToExec << endl;
}

Form::Form( string const name, const int gradeToSign, const int gradeToExec, const bool isSigned):
	_name(name),
	_gradeToSign(gradeToSign),
	_gradeToExec(gradeToExec),
	_signed(isSigned)
{
	cout << "Form Constructor called for " << _name << " with grades required (sign/exec): "
		<< gradeToSign << "/" << gradeToExec << endl;
	_checkRequiredGrades();
};

Form::Form( const Form &other): 
	_name(other._name + "_copy"), 
	_gradeToSign(other._gradeToSign),
	_gradeToExec(other._gradeToExec),
	_signed(other._signed)
{
	cout << "Form Copy Constructor called to copy " << other._name << " into " << _name
		<< " with grades required (sign/exec): " << _gradeToSign << "/" << _gradeToExec << endl;
};

//	Deconstructor
Form::~Form() {
	std::cout << "Form Deconstructor for " << this->getName() << " called" << std::endl;
}

//	Getter
string	Form::getName( void ) const {
	return _name;
}

int		Form::getGradeToSign( void ) const {
	return _gradeToSign;
}

int		Form::getGradeToExec( void ) const {
	return _gradeToExec;
}

bool	Form::isSigned( void ) const {
	return _signed;
}

//	Stream Operators
std::ostream	&operator<<(std::ostream &o, const Form &f) {
	o << std::boolalpha
		<< "Form " << f.getName() << ":" << endl 
		<< "  Required grade to sign : " << f.getGradeToSign() << endl
		<< "  Required grade to exec : " << f.getGradeToExec() << endl
		<< "  Form is signed         : " << f.isSigned();
	return o;
}

// Private Methods
void	Form::_checkRequiredGrades( void ) const {

	if (_gradeToSign < MaxGrade || _gradeToExec < MaxGrade)
		throw GradeTooHighException();
	else if (_gradeToSign > MinGrade || _gradeToExec > MinGrade)
		throw GradeTooLowException();
}

// Public Methods
void	Form::beSigned( const Bureaucrat &b )
{
	if ( b.getGrade() > _gradeToSign )
		throw Form::GradeTooLowException();
	_signed = true;
}

const char *Form::GradeTooHighException::what(void) const throw() {
    return "Form required grade is too high (value is less than 1).";
}

const char *Form::GradeTooLowException::what(void) const throw() {
    return "Form required grade is too low (value is greater than 150), or bureaucrat grade is too low to sign/execute this form.";
}
