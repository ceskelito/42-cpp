#pragma once

#include <string>
#include "Contact.class.hpp"

typedef std::string string;

static const int n_cnt = 8;

class PhoneBook {

private:
	Contact contacts[n_cnt];

public:
	void add_contact(void);

	void search_contact(void);

	void program_loop(void);

	void exit(void);
};
