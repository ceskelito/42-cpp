#pragma once

#include "AForm.class.hpp"

using std::string;

class ShrubberyCreationForm : public AForm {

	private:

	// Attributes
		enum {
				_gradeToSign = 145,
				_gradeToExec = 137	};
		bool	_signed;
		string	_target;

	// Constructors
		ShrubberyCreationForm (void);

	// Overloaded Operators
		AForm	&operator= (const ShrubberyCreationForm &other);

	public:

	// Constructors
		ShrubberyCreationForm (string target);
		ShrubberyCreationForm (ShrubberyCreationForm const &other);

	// Destructor
		~ShrubberyCreationForm (void);

	// Methods
	void	execute(Bureaucrat const & executor) const;
};
