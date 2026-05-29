#pragma once

#include "AForm.class.hpp"
#include "Bureaucrat.class.hpp"

using std::string;

class ShrubberyCreationForm : public AForm {

	private:
		enum { _gradeToSign = 145, _gradeToExec = 137 };
		string	_target;

		// Unused but required
		ShrubberyCreationForm (void);
		AForm	&operator= (const ShrubberyCreationForm &other);

	public:

	// Constructors / Destructor
		ShrubberyCreationForm (string target);
		ShrubberyCreationForm (ShrubberyCreationForm const &other);
		~ShrubberyCreationForm (void);

		void	execute(Bureaucrat const & executor) const;

};
