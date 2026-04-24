#include "Bureaucrat.class.hpp"
#include "Form.class.hpp"

#include <iostream>

static void printTitle(const std::string &title)
{
	std::cout << "\n============================================================" << std::endl;
	std::cout << title << std::endl;
	std::cout << "============================================================" << std::endl;
}

static void printFormState(const std::string &label, const Form &form)
{
	std::cout << "\n[" << label << "]" << std::endl;
	std::cout << form << std::endl;
}

static void showcaseConstruction()
{
	printTitle("1) CONSTRUCTION SHOWCASE (valid + limits)");

	std::cout << "\nDefault form:" << std::endl;
	Form defaultForm;
	printFormState("defaultForm", defaultForm);

	std::cout << "\nValid boundary forms:" << std::endl;
	Form topSecurity("TopSecurity", 1, 1, false);
	Form lowestSecurity("LowestSecurity", 150, 150, false);
	printFormState("topSecurity", topSecurity);
	printFormState("lowestSecurity", lowestSecurity);

	std::cout << "\nValid mixed requirements:" << std::endl;
	Form mixed("MixedPolicy", 42, 100, false);
	printFormState("mixed", mixed);

	std::cout << "\nInvalid construction cases (expected exceptions):" << std::endl;
	try
	{
		Form badSignHigh("BadSignHigh", 0, 50, false);
		(void)badSignHigh;
	}
	catch (const std::exception &e)
	{
		std::cout << "- sign grade 0 -> " << e.what() << std::endl;
	}

	try
	{
		Form badExecHigh("BadExecHigh", 20, 0, false);
		(void)badExecHigh;
	}
	catch (const std::exception &e)
	{
		std::cout << "- exec grade 0 -> " << e.what() << std::endl;
	}

	try
	{
		Form badSignLow("BadSignLow", 151, 50, false);
		(void)badSignLow;
	}
	catch (const std::exception &e)
	{
		std::cout << "- sign grade 151 -> " << e.what() << std::endl;
	}

	try
	{
		Form badExecLow("BadExecLow", 20, 151, false);
		(void)badExecLow;
	}
	catch (const std::exception &e)
	{
		std::cout << "- exec grade 151 -> " << e.what() << std::endl;
	}
}

static void showcaseCopyAndImmutability()
{
	printTitle("2) COPY + IMMUTABILITY SHOWCASE");

	Form original("PermitA", 20, 15, false);
	Form copy(original);

	printFormState("original", original);
	printFormState("copy", copy);

	std::cout << "\nNote: Form assignment operator is intentionally forbidden (private)," << std::endl;
	std::cout << "because name and required grades are immutable (const attributes)." << std::endl;
}

static void showcaseSigningWithBeSigned()
{
	printTitle("3) SIGNING SHOWCASE WITH Form::beSigned");

	Form taxForm("TaxForm", 50, 25, false);
	Bureaucrat chief("Chief", 1);
	Bureaucrat intern("Intern", 150);
	Bureaucrat exactSigner("ExactSigner", 50);

	printFormState("taxForm before", taxForm);

	std::cout << "\nAttempt with low-ranked bureaucrat (should fail):" << std::endl;
	try
	{
		taxForm.beSigned(intern);
		std::cout << "Unexpected: Intern signed the form." << std::endl;
	}
	catch (const std::exception &e)
	{
		std::cout << "Caught: " << e.what() << std::endl;
	}
	printFormState("taxForm after intern attempt", taxForm);

	std::cout << "\nAttempt with exact required grade (50, should succeed):" << std::endl;
	try
	{
		taxForm.beSigned(exactSigner);
		std::cout << "ExactSigner signed the form." << std::endl;
	}
	catch (const std::exception &e)
	{
		std::cout << "Unexpected exception: " << e.what() << std::endl;
	}
	printFormState("taxForm after exactSigner", taxForm);

	std::cout << "\nSecond sign attempt on already signed form (current implementation):" << std::endl;
	try
	{
		taxForm.beSigned(chief);
		std::cout << "Chief called beSigned on an already signed form." << std::endl;
	}
	catch (const std::exception &e)
	{
		std::cout << "Exception: " << e.what() << std::endl;
	}
	printFormState("taxForm final", taxForm);
}

static void showcaseSigningWithBureaucratFacade()
{
	printTitle("4) INTERACTION SHOWCASE WITH Bureaucrat::signForm");

	Form nda("NDA", 10, 10, false);
	Bureaucrat manager("Manager", 10);
	Bureaucrat guest("Guest", 120);

	printFormState("nda before", nda);

	std::cout << "\nGuest tries through Bureaucrat::signForm:" << std::endl;
	guest.signForm(nda);
	std::cout << std::endl;
	printFormState("nda after guest", nda);

	std::cout << "\nManager tries through Bureaucrat::signForm:" << std::endl;
	manager.signForm(nda);
	std::cout << std::endl;
	printFormState("nda after manager", nda);

	std::cout << "\nObserve printed messages and form state: this section highlights"
		<< " real interaction behavior (including edge messaging)." << std::endl;
}

int main(void)
{
	printTitle("FORM CLASS SHOWCASE");
	std::cout << "This executable is a manual showcase (human-verified), not an auto test suite." << std::endl;

	showcaseConstruction();
	showcaseCopyAndImmutability();
	showcaseSigningWithBeSigned();
	showcaseSigningWithBureaucratFacade();

	printTitle("END OF SHOWCASE");
	return 0;
}
