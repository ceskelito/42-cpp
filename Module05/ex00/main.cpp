#include "Bureaucrat.class.hpp"
#include <iostream>
#include <sstream>
#include <string>

// This test suite is wrote by GPT-5.3-Codex

// This test suite is designed to thoroughly test the functionality of the Bureaucrat class. It covers the following aspects:
// 1. Default constructor: Verifies that the default constructor initializes the name and grade correctly.
// 2. Valid construction: Tests that constructing Bureaucrats with valid grades (1, 75, 150) works as expected.
// 3. Invalid construction: Ensures that constructing Bureaucrats with out-of-range grades (0 and 151) throws the appropriate exceptions.
// 4. Increment and decrement: Checks that incrementing and decrementing the grade works correctly and modifies the grade as expected.
// 5. Boundary operations: Verifies that incrementing a grade of 1 and decrementing a grade of 150 throws the appropriate exceptions.
// 6. Copy and assignment: Tests the copy constructor and assignment operator to ensure they copy the grade correctly and handle the name as specified.
// 7. Stream operator: Validates that the overloaded stream operator formats the output correctly

static int g_passed = 0;
static int g_failed = 0;

static void report(bool condition, const std::string &testName)
{
	if (condition)
	{
		++g_passed;
		std::cout << "[PASS] " << testName << std::endl;
	}
	else
	{
		++g_failed;
		std::cout << "[FAIL] " << testName << std::endl;
	}
}

static void testDefaultConstructor()
{
	std::cout << "\n=== Default constructor ===" << std::endl;
	Bureaucrat b;
	report(b.getName() == "BobTheChairHeater", "Default name is BobTheChairHeater");
	report(b.getGrade() == 150, "Default grade is 150");
}

static void testValidConstruction()
{
	std::cout << "\n=== Valid construction ===" << std::endl;
	Bureaucrat high("High", 1);
	Bureaucrat mid("Mid", 75);
	Bureaucrat low("Low", 150);

	report(high.getGrade() == 1, "Grade 1 is accepted");
	report(mid.getGrade() == 75, "Grade 75 is accepted");
	report(low.getGrade() == 150, "Grade 150 is accepted");
}

static void testInvalidConstruction()
{
	std::cout << "\n=== Invalid construction ===" << std::endl;
	bool highThrown = false;
	bool lowThrown = false;

	try
	{
		Bureaucrat tooHigh("Boss", 0);
		(void)tooHigh;
	}
	catch (const Bureaucrat::GradeTooHighException &e)
	{
		highThrown = true;
		std::cout << "Caught expected GradeTooHighException: " << e.what() << std::endl;
	}
	catch (...)
	{
		highThrown = false;
	}

	try
	{
		Bureaucrat tooLow("Intern", 151);
		(void)tooLow;
	}
	catch (const Bureaucrat::GradeTooLowException &e)
	{
		lowThrown = true;
		std::cout << "Caught expected GradeTooLowException: " << e.what() << std::endl;
	}
	catch (...)
	{
		lowThrown = false;
	}

	report(highThrown, "Constructing with grade 0 throws GradeTooHighException");
	report(lowThrown, "Constructing with grade 151 throws GradeTooLowException");
}

static void testIncrementDecrement()
{
	std::cout << "\n=== Increment and decrement ===" << std::endl;
	Bureaucrat b("Worker", 2);
	b.incrementGrade();
	report(b.getGrade() == 1, "incrementGrade decreases numeric value");

	b.decrementGrade();
	report(b.getGrade() == 2, "decrementGrade increases numeric value");
}

static void testBoundaryOperations()
{
	std::cout << "\n=== Boundary operations ===" << std::endl;
	bool highThrown = false;
	bool lowThrown = false;

	try
	{
		Bureaucrat top("Top", 1);
		top.incrementGrade();
	}
	catch (const Bureaucrat::GradeTooHighException &e)
	{
		highThrown = true;
		std::cout << "Caught expected GradeTooHighException on increment: " << e.what() << std::endl;
	}

	try
	{
		Bureaucrat bottom("Bottom", 150);
		bottom.decrementGrade();
	}
	catch (const Bureaucrat::GradeTooLowException &e)
	{
		lowThrown = true;
		std::cout << "Caught expected GradeTooLowException on decrement: " << e.what() << std::endl;
	}

	report(highThrown, "Incrementing grade 1 throws GradeTooHighException");
	report(lowThrown, "Decrementing grade 150 throws GradeTooLowException");
}

static void testCopyAndAssignment()
{
	std::cout << "\n=== Copy and assignment ===" << std::endl;
	Bureaucrat source("Alice", 42);
	Bureaucrat copied(source);

	report(copied.getGrade() == 42, "Copy constructor copies grade");
	report(copied.getName() == "Alice_copy", "Copy constructor applies _copy suffix to name");

	Bureaucrat lhs("Left", 120);
	Bureaucrat rhs("Right", 7);
	lhs = rhs;
	report(lhs.getGrade() == 7, "Assignment operator copies grade");
	report(lhs.getName() == "Left", "Assignment operator keeps original name");

	lhs = lhs;
	report(lhs.getGrade() == 7, "Self-assignment keeps state stable");
}

static void testStreamOperator()
{
	std::cout << "\n=== Stream operator ===" << std::endl;
	Bureaucrat b("Printer", 33);
	std::ostringstream oss;
	oss << b;
	std::cout << "operator<< test: " << b << std::endl;
	report(oss.str() == "Printer, bureaucrat grade 33", "operator<< formatting is correct");
}

int main ( void )
{
	std::cout << "Starting Bureaucrat test suite..." << std::endl;

	testDefaultConstructor();
	testValidConstruction();
	testInvalidConstruction();
	testIncrementDecrement();
	testBoundaryOperations();
	testCopyAndAssignment();
	testStreamOperator();

	std::cout << "\n=== Test summary ===" << std::endl;
	std::cout << "Passed: " << g_passed << std::endl;
	std::cout << "Failed: " << g_failed << std::endl;

	if (g_failed == 0)
	{
		std::cout << "All tests passed." << std::endl;
		return 0;
	}

	std::cout << "Some tests failed." << std::endl;
	return 1;
}
