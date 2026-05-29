#pragma once

#include "AForm.class.hpp"
#include "Bureaucrat.class.hpp"

using std::string;

class RobotomyRequestForm : public AForm {

	private:
		enum { _gradeToSign = 72, _gradeToExec = 45 };
		string	_target;

		// Unused but required
		RobotomyRequestForm (void);
		AForm	&operator= (const RobotomyRequestForm &other);

	public:

	// Constructors / Destructor
		RobotomyRequestForm (string target);
		RobotomyRequestForm (RobotomyRequestForm const &other);
		~RobotomyRequestForm (void);

		void	execute(Bureaucrat const & executor) const;

};
