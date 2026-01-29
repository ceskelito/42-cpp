#include "Harl.class.hpp"
#include <bits/stdc++.h>
#include <iostream>

void	Harl::_debug(void) {
	std::cout << "I love having extra bacon for my 7XL-double-cheese-triple-pickle-special-ketchup burger. I really do!";
	std::cout << std::endl;
}

void	Harl::_info(void) {
	std::cout << "I cannot believe adding extra bacon costs more money. You didn’t put enough bacon in my burger! If you did, I wouldn’t be asking for more!";
	std::cout << std::endl;
}

void	Harl::_warning(void) {
	std::cout << "I think I deserve to have some extra bacon for free. I’ve been coming for years, whereas you started working here just last month.";
	std::cout << std::endl;
}

void	Harl::_error(void) {
	std::cout << "This is unacceptable! I want to speak to the manager now.";
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
