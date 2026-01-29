#include "Harl.class.hpp"
#include <bits/stdc++.h>
#include <iostream>

void	Harl::_debug(void) {
	std::cout << "[DEBUG]" << std::endl;
	std::cout << "I love having extra bacon for my 7XL-double-cheese-triple-pickle-special-ketchup burger.\nI really do!";
	std::cout << std::endl;
}

void	Harl::_info(void) {
	std::cout << "[INFO]" << std::endl;
	std::cout << "I cannot believe adding extra bacon costs more money. You didn’t put enough bacon in my burger!\nIf you did, I wouldn’t be asking for more!";
	std::cout << std::endl;
}

void	Harl::_warning(void) {
	std::cout << "[WARNING]" << std::endl;
	std::cout << "I think I deserve to have some extra bacon for free.\nI’ve been coming for years, whereas you started working here just last month.";
	std::cout << std::endl;
}

void	Harl::_error(void) {
	std::cout << "[ERROR]" << std::endl;
	std::cout << "This is unacceptable!\nI want to speak to the manager now.";
	std::cout << std::endl;
}

// Public methods

void	Harl::complain(std::string level) {

	void		(Harl::*complain_ptr[])(void) = {&Harl::_debug, &Harl::_info, &Harl::_warning, &Harl::_error};
	std::string complain_levels[] = {"DEBUG", "INFO", "WARNING", "ERROR"};

	// idk if transform is in c++98
	// transform(level.begin(), level.end(), level.begin(), ::toupper);

	for (int i = 0; i < 4; i++) {
		if (level == complain_levels[i]) {
			(this->*complain_ptr[i])();
			break ;
		}
	}
}
