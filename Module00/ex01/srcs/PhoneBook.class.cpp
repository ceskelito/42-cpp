#include "PhoneBook.class.hpp"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <stdlib.h>

static std::ostream &bold_on(std::ostream &os) {
	return os << "\e[1m";
}

static std::ostream &bold_off(std::ostream &os) {
	return os << "\e[0m";
}

void PhoneBook::get_field(string field_name, string &field) {
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

void PhoneBook::print_column(string column_name, char delimiter) {
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

void PhoneBook::print_column(string column_name) {
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

	if (this->_index == this->_max_index)
		this->_index = 0;

	if (this->_count < this->_max_index + 1)
		this->_count++;

	this->get_field("First Name", f_name);
	this->get_field("Last Name", l_name);
	this->get_field("Nick Name", n_name);
	do {
		this->get_field("Phone Number", number);
		if (number.find_first_not_of("0123456789") != string::npos)
			std::cout<< std::endl << "The 'Phone Number' field must contain only digits";
		else if (number.length() != 10)
			std::cout << std::endl << "The 'Phone Number' field must be of length 10";
	} while(number.length() != 10 || number.find_first_not_of("0123456789") != string::npos);
	get_field("Dark Secret", secret);
	this->_contacts[this->_index] = Contact(f_name, l_name, n_name, number, secret);
	this->_index++;
};

void PhoneBook::exit(void) {

	std::cout << "Say goodbye to your contacts!" << std::endl;
	std::cout << "What, didn't I warn you that you'll lose all the contact once you close the PhoneBook?" << std::endl;
	std::cout << "Oh... I hope you have a good memory." << std::endl;
	std::exit(EXIT_SUCCESS);
};

void PhoneBook::search_contact()
{
	using	std::cout;
		
	std::stringstream ss;
	string index;
	Contact *curr;

	this->print_column("index", '|');
	this->print_column("last name", '|');
	this->print_column("nick name", '|');
	this->print_column("nickname");
	cout << std::endl;
	for (int i = 0; i < this->_count; i++)
	{
		ss << i;
		index = ss.str();
		curr = &this->_contacts[i];
		this->print_column(index, '|');
		this->print_column(curr->get_last(), '|');
		this->print_column(curr->get_first(), '|');
		this->print_column(curr->get_nick());
		cout << std::endl;
	}
	return ;
}

void PhoneBook::program_loop(void) {

	using std::cout;
	using std::endl;

	string	input;

	while (1)
	{
		cout << endl;
		cout << bold_on << "ADD" << bold_off << " - Add a contact" << endl;
		cout << bold_on << "SEARCH" << bold_off << " - Search for a saved contact" << endl;
		cout << bold_on << "EXIT" << bold_off <<" - Close the PhoneBook and exit the program" << endl;
		cout << endl << "Option: ";
		
		getline(std::cin, input);
		if (std::cin.eof())
			std::exit(EXIT_FAILURE);

		if (input == "ADD") {
			cout << std::endl;
			this->add_contact();
		} else if (input == "SEARCH") {
			cout << std::endl;
			this->search_contact();
		} else if (input == "EXIT"){
			cout << std::endl;
			this->exit();
		} else {
			cout << "Unknown option: " << input << std::endl;
		}
		
	}
}

PhoneBook::PhoneBook(void) : _index(0), _count(0) {};
PhoneBook::~PhoneBook(void){};
