#include "Contact.class.hpp"

// Default Constructor
Contact::Contact(void) :
				_first_name("FirstName"),
				_last_name("LastName"),
				_nick_name("NickName"),
				_phone_number("123456789"),
				_dark_secret("DarkSecret") {};

// Parametrized Constructor
Contact::Contact(string first_name,
				 string last_name,
				 string nick_name,
				 string phone_number,
				 string dark_secret) :

				_first_name(first_name),
				_last_name(last_name),
				_nick_name(nick_name),
				_phone_number(phone_number),
				_dark_secret(dark_secret) {};

// Destructor
Contact::~Contact(void) {};

// Copy Constructor
Contact::Contact(const Contact &other) : 
				_first_name(other._first_name),
				_last_name(other._last_name),
				_nick_name(other._nick_name),
				_phone_number(other._phone_number),
				_dark_secret(other._dark_secret) {};

// Assignment Operator
Contact &Contact::operator=(const Contact &other) {

	if (this != &other)
	{
		_first_name = other._first_name;
		_last_name = other._last_name;
		_nick_name = other._nick_name;
		_phone_number = other._phone_number;
		_dark_secret = other._dark_secret;
	}
	return (*this);
};
