#include "PhoneBook.class.hpp"
#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include "utils.hpp"


void PhoneBook::_input_field(string field_name, string &field) {
	using std::cin;
	using std::cout;
	using std::endl;
	
	do {
		cout << endl << field_name << ": ";
		GET_LINE(cin, field);
		if (field.empty()) {
			cout << red << "The field '" << field_name << "' can not be empty" << reset << endl;
			wait_for_input();
			clear_lines(std::cout, 5);
			continue;
		}
	} while(field.empty());

}

void PhoneBook::_print_column(string column_name, char delimiter) {
	using std::cout;
	using std::setw;

	cout << std::right;

	if (column_name.length() > this->_column_width)
	{
		column_name.resize(this->_column_width - 1);
		column_name.append(".");
	}

	cout << std::setw(10) << column_name;
	cout << delimiter;

	cout << std::left;
}

void PhoneBook::_print_column(string column_name) {
	using std::cout;
	using std::setw;

	cout << std::right;

	if (column_name.length() > this->_column_width)
	{
		column_name.resize(this->_column_width - 1);
		column_name.append(".");
	}

	cout << std::setw(10) << column_name;

	cout << std::left;
}

void PhoneBook::add_contact(void) {


	string	f_name;
	string	l_name;
	string	n_name;
	string	number;
	string	secret;

	std::cout << blue << "Adding a new contact" << reset << std::endl;

	if (this->_index > this->_max_index)
		this->_index = 0;

	if (this->_count < this->_max_index + 1)
		this->_count++;

	this->_input_field("First Name", f_name);
	this->_input_field("Last Name", l_name);
	this->_input_field("Nick Name", n_name);
	do {
		this->_input_field("Phone Number", number);
		if (number.find_first_not_of("0123456789") != string::npos) {
			std::cout << red << "The 'Phone Number' field must contain only digits" << reset << std::endl;
		}
		else if (number.length() != 10) {
			std::cout << red << "The 'Phone Number' field must be of length 10" << reset << std::endl;
		}
		else break;
		wait_for_input();
		clear_lines(std::cout, 5);
	} while(true);
	this->_input_field("Dark Secret", secret);
	this->_contacts[this->_index] = Contact(f_name, l_name, n_name, number, secret);
	this->_index++;
	std::cout <<std::endl << blue << "Contact saved succesfully!" << reset << std::endl;
	press_enter_to_continue();
};

void PhoneBook::exit(void) {

	std::cout << bold << "Say goodbye to your contacts!" << reset << std::endl <<std::endl;
	std::cout << "What, didn't I warn you that you'll lose all the contact once you close the PhoneBook?" << std::endl;
	std::cout << "Oh... I hope you have a good memory..." << std::endl << std::endl;
	std::exit(EXIT_SUCCESS);
};

void PhoneBook::_print_table(void) {

	Contact *curr;

	std::cout << std::endl;
	this->_print_column("index", '|');
	this->_print_column("First Name", '|');
	this->_print_column("Last Name", '|');
	this->_print_column("Nickname");
	std::cout << std::endl;
	for (int i = 0; i < this->_count; i++)
	{
		curr = &this->_contacts[i];
		this->_print_column(itostr(i), '|');
		this->_print_column(curr->get_first(), '|');
		this->_print_column(curr->get_last(), '|');
		this->_print_column(curr->get_nick());
		std::cout << std::endl;
	}
}

void PhoneBook::_print_info(Contact &contact) {
	using std::cout;
	using std::endl;

	cout << clear << endl;
	cout << bold << blue << "Contact Information" << reset << endl << endl;
	cout << std::right << bold << std::setw(15) << "First Name: " << reset << contact.get_first() << endl;
	cout << std::right << bold << std::setw(15) << "Last Name: " << reset << contact.get_last() << endl;
	cout << std::right << bold << std::setw(15) << "Nick Name: "<< reset << contact.get_nick() << endl;
	cout << std::right << bold << std::setw(15) << "Phone Number: " << reset << contact.get_number() << endl;
	cout << std::right << bold << std::setw(15) << "Dark Secret: " << reset << contact.get_secret() << endl;
	press_enter_to_continue();
}

void PhoneBook::search_contact()
{
	using	std::cout;
	string	input;
	int		index;

	if (this->_count == 0) {
		cout << blue << "There are no saved contacts yet" << reset;
		press_enter_to_continue();
		return ;
	}

	cout << blue << "Searching for a contact" << std::endl;
	cout << std::endl << green << "Select an index" << reset << std::endl;
	this->_print_table();

	do {
		cout << std::endl << "> ";
		GET_LINE(std::cin, input);
		index = std::atoi(input.c_str());
		if (input.find_first_not_of("0123456789") != std::string::npos) {
			cout << red << "The index has to be an integer" << reset << std::endl;
		} else if (index < 0 || index > this->_count - 1) {
			cout << red << "Index out of range" << reset << std::endl;
		}
		else break;
		wait_for_input();
		clear_lines(std::cout, 5);
	} while (true);

	this->_print_info(this->_contacts[index]);	
	return ;
}

void PhoneBook::program_loop(void) {

	using std::cout;
	using std::endl;

	string	input;

	while (1)
	{
		cout << clear;
		cout << endl << green << "Select an option from below" << reset << endl << endl;
		cout << bold << std::left << std::setw(7) << "ADD" << reset << " - Add a new contact" << endl;
		cout << bold << std::left << std::setw(7) << "SEARCH" << reset << " - Search for a saved contact" << endl;
		cout << bold << std::left << std::setw(7) << "EXIT" << reset <<" - Close the PhoneBook and exit the program" << endl;
		cout << endl << "> ";

		GET_LINE(std::cin, input);

		if (input == "ADD") {
			cout << clear;
			cout << std::endl;
			this->add_contact();
		} else if (input == "SEARCH") {
			cout << clear;
			cout << std::endl;
			this->search_contact();
		} else if (input == "EXIT"){
			cout << clear;
			cout << std::endl;
			this->exit();
		} else {
			cout << std::endl;
			cout << red << "Unknown option: `" << bold << input << reset << red << "'" << reset;// << std::endl;
			wait_for_input();
		}
	}
}

PhoneBook::PhoneBook(void) : _index(0), _count(0) {};
PhoneBook::~PhoneBook(void){};
