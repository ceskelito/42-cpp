#pragma once

#include <string>
#include "AForm.class.hpp"

class Intern {

	private:
	public:
		Intern ( void );
		Intern ( Intern & other );
		~Intern ( void );
		Intern &operator=( Intern & other );

		AForm	*makeForm( std::string const &form, std::string const &target ) const;
};
