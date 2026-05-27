#include "AForm.class.hpp"
#include "Bureaucrat.class.hpp"

#include <iostream>
#include <ostream>

using std::string;
using std::cout;
using std::endl;

static string className( void ) {

	const string BLD = "\e[1m";
	const string ITL = "\e[3m";
	const string RST = "\e[0m";

	return (string(BLD) + ITL + "[ AForm ]" + RST);
}

//	Constructors
AForm::AForm(void): _name("GenericForm"), _gradeToSign(MinGrade), _gradeToExec(MinGrade), _signed(false) {
	cout << className() << " Default Constructor called for " << _name << " with grades required (sign/exec): "
		<< _gradeToSign << "/" << _gradeToExec << endl;
}

AForm::AForm( string const name, const int gradeToSign, const int gradeToExec, const bool isSigned):
	_name(name),
	_gradeToSign(gradeToSign),
	_gradeToExec(gradeToExec),
	_signed(isSigned)
{
	cout << className() << " Constructor called for " << _name << " with grades required (sign/exec): "
		<< _gradeToSign << "/" << _gradeToExec << endl;
	_checkRequiredGrades();
};

AForm::AForm( string const name, const int gradeToSign, const int gradeToExec):
	_name(name),
	_gradeToSign(gradeToSign),
	_gradeToExec(gradeToExec),
	_signed(false)
{
	cout << className() << " Constructor called for " << _name << " with grades required (sign/exec): "
		<< _gradeToSign << "/" << _gradeToExec << endl;
	_checkRequiredGrades();
};

AForm::AForm( const AForm &other): 
	_name(other._name + "_copy"), 
	_gradeToSign(other._gradeToSign),
	_gradeToExec(other._gradeToExec),
	_signed(other._signed)
{
	cout << className() << " Copy Constructor called to copy " << other._name << " into " << _name
		<< " with grades required (sign/exec): " << _gradeToSign << "/" << _gradeToExec << endl;
};

//	Deconstructor
AForm::~AForm() {
	std::cout << className() << " Destructor called for " << this->getName() << " called" << std::endl;
}

//	Getter
string	AForm::getName( void ) const {
	return _name;
}

int		AForm::getGradeToSign( void ) const {
	return _gradeToSign;
}

int		AForm::getGradeToExec( void ) const {
	return _gradeToExec;
}

bool	AForm::isSigned( void ) const {
	return _signed;
}

//	Stream Operators
std::ostream	&operator<<(std::ostream &o, const AForm &f) {
	o << std::boolalpha
		<< "Form " << f.getName() << ":" << endl 
		<< "  Required grade to sign : " << f.getGradeToSign() << endl
		<< "  Required grade to exec : " << f.getGradeToExec() << endl
		<< "  Form is signed         : " << f.isSigned();
	return o;
}

// Private Methods
void	AForm::_checkRequiredGrades( void ) const {

	if (_gradeToSign < MaxGrade || _gradeToExec < MaxGrade)
		throw GradeTooHighException();
	else if (_gradeToSign > MinGrade || _gradeToExec > MinGrade)
		throw GradeTooLowException();
}

// Public Methods
void	AForm::beSigned( const Bureaucrat &b )
{
	if ( b.getGrade() > _gradeToSign )
		throw AForm::GradeTooLowException();
	_signed = true;
}

const char *AForm::GradeTooHighException::what(void) const throw() {
    return "Form required grade is too high (value is less than 1).";
}

const char *AForm::GradeTooLowException::what(void) const throw() {
    return "Form required grade is too low (value is greater than 150), or bureaucrat grade is too low to sign/execute this form.";
}
