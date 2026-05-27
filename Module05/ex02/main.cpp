#include "Bureaucrat.class.hpp"
#include "ShrubberyCreationForm.class.hpp"
#include "AnsiColorCodes.h"
#include <iostream>

using std::cout;
using std::endl;

int main(void)
{
	cout << BLU << "Creating a Form:" << WHT << endl;
	ShrubberyCreationForm	first("BeatifulTree");
	cout << endl;

	cout << BLU << "Creating a copy from the first Form:" << WHT << endl;
	ShrubberyCreationForm	second(first);
	cout << endl;

	cout << BLU << "Creating a Bureaucrat:" << WHT << endl;
	Bureaucrat				b("Bobby", 10);
	cout << endl;

	first.execute(b);
	return 0;
}
