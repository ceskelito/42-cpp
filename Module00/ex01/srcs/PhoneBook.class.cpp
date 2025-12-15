#include "PhoneBook.class.hpp"
#include <iostream>
#include <stdlib.h>

static std::ostream &bold_on(std::ostream &os) {
	return os << "\e[1m";
}

static std::ostream &bold_off(std::ostream &os) {
	return os << "\e[0m";
}

static void get_field(string field_name, string &field)
{
	using std::cin;
	using std::cout;
	
	do {
		cout << std::endl << field_name << ": ";
		getline(cin, field);
		if (field.empty())
		{
			cout << std::endl << "The field '" << field_name << "' can not be empty";
			continue;
		}
	} while(field.empty());

}

void PhoneBook::add_contact(void) {


	string	f_name;
	string	l_name;
	string	n_name;
	string	number;
	string	secret;

	if (this->_index == this->_max_index)
		this->_index = 0;

	if (this->_count < this->_max_index)
		this->_count++;

	get_field("First Name", f_name);
	get_field("Last Name", l_name);
	get_field("Nick Name", n_name);
	do {
		get_field("Phone Number", number);
		if (number.find_first_not_of("0123456789") != string::npos)
			std::cout<< std::endl << "The 'Phone Number' field must contain only digits";
		else if (number.length() != 10)
			std::cout << std::endl << "The 'Phone Number' field must be of length 10";
	} while(number.length() != 10 || number.find_first_not_of("0123456789") != string::npos);
	get_field("Dark Secret", secret);
	this->_contacts[this->_index] = Contact(f_name, l_name, n_name, number, secret);
};

void PhoneBook::exit(void) {

	std::cout << "Say goodbye to your contacts!" << std::endl;
	std::cout << "What, didn't I warn you that you'll lose all the contact once you close the PhoneBook?" << std::endl;
	std::cout << "Oh... I hope you have a good memory." << std::endl;
	::exit(EXIT_SUCCESS);
};

void PhoneBook::search_contact()
{
	return ;
}

void PhoneBook::program_loop(void) {

	using std::cout;

	string	input;

	while (1)
	{
		cout << bold_on << "ADD" << bold_off << " - Add a contact" << std::endl;
		cout << bold_on << "SEARCH" << bold_off << " - Search for a saved contact" << std::endl;
		cout << bold_on << "EXIT" << bold_off <<" - Close the PhoneBook and exit the program" << std::endl << std::endl;
		cout << "Option: ";

		getline(std::cin, input);

		if (input == "ADD") {
			this->add_contact();
		} else if (input == "SEARCH") {
			this->search_contact();
		} else if (input == "EXIT"){
			this->exit();
		} else {
			cout << "Unknown option: " << input << std::endl;
		}
		
	}
}

PhoneBook::PhoneBook(void) : _index(0), _count(0) {};
PhoneBook::~PhoneBook(void){};
