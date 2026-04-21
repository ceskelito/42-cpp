#pragma once

#include <string>
#include <exception>

class Bureaucrat {

	private:

	enum { MaxGrade = 1, MinGrade = 150};

	// Setter
		void	_setGrade( int grade );

	// Attributes
		const std::string	_name;
		int					_grade;

	public:
	// Constructors
		Bureaucrat( void );
		Bureaucrat( const std::string name, int grade );
		Bureaucrat( const Bureaucrat &other );

	// Destructors
		~Bureaucrat( void );

	// Overloaded Operators
		Bureaucrat		&operator=( const Bureaucrat &other );

	// Getter
		std::string	getName( void ) const;
		int			getGrade( void ) const;

	// Public Methods
		void		incrementGrade( void );
		void		decrementGrade( void );


	// Exceptions
	class	GradeTooHighException: std::exception
	{
		public:
			virtual const char *what( void ) const throw();
	};

	class	GradeTooLowException: std::exception
	{
		public:
			virtual const char *what( void ) const throw();
	};
};

//	Stream Operators
std::ostream	&operator<<( std::ostream &o, const Bureaucrat &b );
