#pragma once

#include <string>
#include "Contact.class.hpp"

typedef std::string str;

static const int n_cnt = 8;

class PhoneBook {

private:
	Contact contacts[n_cnt];

public:
	void add(str first_name,
			str last_name,
			str nick_name,
			str phone_number,
			str secret
		  );

	void search(str first_name,
				str last_name
			 );

	void search(str nick_name);

	void start();

	void exit();
};
