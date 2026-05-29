#include "Bureaucrat.class.hpp"
#include "AForm.class.hpp"
#include "Intern.class.hpp"

int main()
{
	Intern Michel;
	AForm* form[3];

	form[0] = Michel.makeForm("robotomy request", "Jean");
	form[1] = Michel.makeForm("Idk", "Edouart");
	form[2] = Michel.makeForm("presidential pardon", "Edouart");

	Bureaucrat Robert("Robert", 35);
	Robert.signForm(*form[0]);
	Robert.executeForm(*form[0]);

	Robert.signForm(*form[2]);

	delete form[0]; delete form[2];
}
