#pragma once

#include "AForm.class.hpp"
#include "Bureaucrat.class.hpp"

using std::string;

class PresidentialPardonForm : public AForm {

	private:
		enum { _gradeToSign = 25, _gradeToExec = 5 };
		string	_target;

		// Unused but required
		PresidentialPardonForm (void);
		AForm	&operator= (const PresidentialPardonForm &other);

	public:

	// Constructors / Destructor
		PresidentialPardonForm (string target);
		PresidentialPardonForm (PresidentialPardonForm const &other);
		~PresidentialPardonForm (void);

		void	execute(Bureaucrat const & executor) const;

};
