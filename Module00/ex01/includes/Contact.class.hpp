#pragma once

#include <string>

using std::string;

class Contact {
	
private:
	string	_first_name;
	string	_last_name;
	string	_nick_name;
	string	_phone_number;
	string	_dark_secret;

public:
	Contact(void);

	Contact(string first_name, string last_name, string nick_name, string phone_number, string dark_secret);

	~Contact(void);

	Contact(const Contact &other);

	Contact &operator=(const Contact &other);// {
};
