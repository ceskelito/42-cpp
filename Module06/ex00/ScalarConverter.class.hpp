#pragma once

#include <string>

class ScalarConverter {

	private:
		// Required but not used
		ScalarConverter ( void );
		ScalarConverter ( ScalarConverter & other);
		ScalarConverter& operator= (ScalarConverter & other);
		~ScalarConverter ( void );

	public:
		static void convert (std::string literal);
};
