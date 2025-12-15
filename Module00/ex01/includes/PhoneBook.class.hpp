#pragma once

#include <string>
#include "Contact.class.hpp"

using std::string;

class PhoneBook {

private:

	static const int	_max_index = 8;
	Contact				_contacts[_max_index];
	int					_index;
	int					_count;

public:

	PhoneBook(void);
	~PhoneBook(void);

	void add_contact(void);
	void search_contact(void);
	void program_loop(void);
	void exit(void);
};
