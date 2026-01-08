#pragma once

#include <string>

using std::string;	

class Weapon {
	
private:
	string _type;

public:
	
	Weapon(string type);

	string	getType(void);
	void	setType(string type);
};
