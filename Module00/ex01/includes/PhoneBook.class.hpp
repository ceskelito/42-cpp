#pragma once

#include <string>
#include "Contact.class.hpp"

using std::string;

class PhoneBook {

private:

	static const int	_column_width = 10;
	static const int	_max_index = 7;
	Contact				_contacts[_max_index + 1];
	int					_index;
	int					_count;

	void				_input_field(string field_name, string &field);
	void				_print_column(string column_name, char delimiter);
	void				_print_column(string column_name);
	void				_print_table(void);
	void				_print_info(Contact &contact);

public:

	PhoneBook(void);
	~PhoneBook(void);

	void add_contact(void);
	void search_contact(void);
	void program_loop(void);
	void exit(void);
};
