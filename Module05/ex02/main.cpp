#include "Bureaucrat.class.hpp"
#include "ShrubberyCreationForm.class.hpp"
#include <iostream>

int main(void)
{
	ShrubberyCreationForm	first("target");
	ShrubberyCreationForm	second(first);
	Bureaucrat				b("name", 10);

	first.execute(b);
	return 0;
}
