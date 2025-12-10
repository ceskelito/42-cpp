#include "Contact.class.hpp"

Contact::Contact() : _name("Default"), _prefix("+39"), _number("123456789") {
	// Default Constructor
};
	
Contact::Contact(std::string name, std::string prefix, std::string number) : _name(name), _prefix(prefix), _number(number) {
	// Parameterized Constructor
};

Contact::~Contact() {
	// Destructor
};
Contact::Contact(const Contact &other) : _name(other._name), _prefix(other._prefix), _number(other._number) {
	// Copy Constructor
};

// Contact::Contact &operator=(const Contact &other) {
// 	// Assignment Operator
// 	if (this != &other)
// 	{
// 		_name = other._name;
// 		_prefix = other._prefix;
// 		_number = other._number;
// 	}
// 	return (*this);
// }
