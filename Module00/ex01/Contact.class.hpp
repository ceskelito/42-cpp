#pragma once

#include <string>

class Contact {
	
private:
	std::string _name;
	std::string _prefix;
	std::string _number;

public:
	Contact();

	Contact(std::string name, std::string prefix, std::string number);

	~Contact();

	Contact(const Contact &other);

	Contact &operator=(const Contact &other) {
		// Assignment Operator
		if (this != &other)
		{
			_name = other._name;
			_prefix = other._prefix;
			_number = other._number;
		}
		return (*this);
	}
};
