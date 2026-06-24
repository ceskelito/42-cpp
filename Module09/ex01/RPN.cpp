#include <stack>
#include <string>
#include <sstream>

static void	make_op(char op, std::stack<int> & stack) {

	if ( stack.size() < 2 )	{
		throw std::length_error("Too few numbers before operator.");
	}

	long	res;
	int		first_term, second_term;

	second_term = stack.top(); stack.pop();
	first_term = stack.top(); stack.pop();

	if (op == '+')
		res = first_term + second_term;
	else if (op == '-')
		res = first_term - second_term;
	else if (op == '*')
		res = first_term * second_term;
	else if (op == '/') {
		if (second_term == 0)
			throw std::invalid_argument("Division by zero.");
		res = first_term / second_term;
	}

	stack.push(res);
}

long	RPN(std::string const & exp) {

	std::stack<int>		stack_exp;
	std::istringstream	iss(exp);
	
	std::string token;
	while (iss >> token) // Iss will stop extracting at the first space
	{
		if ( std::string("+-*/").find_first_of(token[0]) != std::string::npos )
		{
			if (token.length() != 1)
				throw std::invalid_argument("Invalid operator: " + token);
			make_op(token[0], stack_exp);
		}
		else
		{
			std::stringstream ss(token);
			int n;
			if (!(ss >> n) || !ss.eof() || n < 0 || n > 9) {
				throw std::invalid_argument("Invalid number: " + token);
			}
			stack_exp.push(n);
		}
	}
	if ( stack_exp.size() != 1 ) {
		throw std::length_error("Too many numbers.");
	}
	return stack_exp.top();
}
