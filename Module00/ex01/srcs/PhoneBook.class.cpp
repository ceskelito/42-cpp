#include "PhoneBook.class.hpp"
#include <iostream>
#include <stddef.h>

void PhoneBook::add_contact(void) {

};

void PhoneBook::exit(void) {

	std::cout << "Say goodbye to your contacts!" << std::endl;
	std::cout << "What, didn't I warn you that you'd lose contact once you left the program? Oh... I hope you have a good memory." << std::endl;
	std::exit(EXIT_SUCCESS);
};

void PhoneBook::program_loop(void) {

	std::string	input;

	while (1)
	{
		std::cin >> input;

		if (input == "ADD") {
			this->add_contact();
		} else if (input == "SEARCH") {
			this->search_contact();
		} else if (input == "EXIT"){
			this->exit();
		} else continue;
		
	}
}
