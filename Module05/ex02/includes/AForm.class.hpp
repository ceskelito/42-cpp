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

	// Unused but required (Orthodox Canonical Form)
		AForm( void );
		AForm( const std::string name, const int gradeToSign, const int gradeToExec, const bool isSigned );
		AForm	&operator=( const AForm &other ); // Since the form is immutable, the assignment is forbidden

	protected:
	// Constructors / Destructor
		AForm( const std::string name, const int gradeToSign, const int gradeToExec );
		AForm( const AForm &other );
		virtual ~AForm( void ) = 0;
	
	// Methods
		void			_checkRequiredGrades( void ) const;

	public:
	// Getter
		virtual std::string	getName( void ) const;
		virtual int			getGradeToSign( void ) const;
		virtual int			getGradeToExec( void ) const;
		virtual bool		isSigned( void ) const;

	// Methods
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

	class	ExecuteUnsignedException: public std::exception
	{
		public:
			const char *what( void ) const throw();
	};
};

//	Stream Operators
std::ostream	&operator<<( std::ostream &o, const AForm &f );
