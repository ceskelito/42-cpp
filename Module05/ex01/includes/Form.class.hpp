#pragma once

#include <string>
#include <exception>
#include <ostream>

class Bureaucrat;

class Form {

	private:

	enum { MaxGrade = 1, MinGrade = 150};

	// Attributes
		const std::string	_name;
		const int			_gradeToSign;
		const int			_gradeToExec;
		bool				_signed;
	
	// Private Methods
		void				_checkRequiredGrades( void ) const;

	// Overloaded Operators
	/* Since the form is immutable, the assignment is forbidden */
		Form		&operator=( const Form &other );

	public:
	// Constructors
		Form( void );
		Form( const std::string name, const int gradeToSign, const int gradeToExec, const bool isSigned );
		Form( const Form &other );

	// Destructors
		~Form( void );

	// Getter
		std::string	getName( void ) const;
		int			getGradeToSign( void ) const;
		int			getGradeToExec( void ) const;
		bool		isSigned( void ) const;

	// Public Methods
		void		beSigned( const Bureaucrat &b );

	// Exceptions
	class	GradeTooHighException: public std::exception
	{
		public:
			const char *what( void ) const throw();
	};

	class	GradeTooLowException: public std::exception
	{
		public:
			const char *what( void ) const throw();
	};
};

//	Stream Operators
std::ostream	&operator<<( std::ostream &o, const Form &f );
