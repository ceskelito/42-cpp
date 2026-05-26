#pragma once

#include <string>
#include <exception>
#include <ostream>

class Bureaucrat;

class AForm {

	private:

	enum { MaxGrade = 1, MinGrade = 150};

	// Attributes
		const std::string	_name;
		const int			_gradeToSign;
		const int			_gradeToExec;
		bool				_signed;

	protected:
	// Constructor
		AForm( const std::string name, const int gradeToSign, const int gradeToExec, const bool isSigned );
	
	// Private Methods
		void				_checkRequiredGrades( void ) const;

	// Overloaded Operators
	/* Since the form is immutable, the assignment is forbidden */
		AForm		&operator=( const AForm &other );

	// Constructors
		AForm( void );
		AForm( const std::string name, const int gradeToSign, const int gradeToExec );
		AForm( const AForm &other );

	// Destructors
		virtual ~AForm( void ) = 0;

	public:
	// Getter
		virtual std::string	getName( void ) const;
		virtual int			getGradeToSign( void ) const;
		virtual int			getGradeToExec( void ) const;
		virtual bool		isSigned( void ) const;

	// Public Methods
		void			beSigned( const Bureaucrat &b );
		virtual void	execute(Bureaucrat const & executor) const = 0;

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
std::ostream	&operator<<( std::ostream &o, const AForm &f );
