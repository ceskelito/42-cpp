/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rceschel <rceschel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 13:51:00 by rceschel          #+#    #+#             */
/*   Updated: 2025/12/16 16:44:48 by rceschel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>
#include <iostream>
#include <sstream>
#include <limits>
#include <ios>

std::ostream &bold(std::ostream &os) {
	return os << "\e[1m";
}

std::ostream &red(std::ostream &os) {
	return os << "\e[31m";
}

std::ostream &green(std::ostream &os) {
	return os << "\e[32m";
}

std::ostream &blue(std::ostream &os) {
	return os << "\e[34m";
}

std::ostream &reset(std::ostream &os) {
	return os << "\e[0m";
}

std::ostream &clear(std::ostream &os) {
	const std::string clear_screen = "\033[2J\033[1;1H";

	return os << clear_screen;
}

void	clear_lines(std::ostream &os, int num_of_lines) {

	for (int i = 0; i < num_of_lines; i++) {
		os << "\033[1A";
		os << "\033[K";
	}
}

std::string itostr(int n) {
	std::stringstream ss;
	ss << n;
	return (ss.str());
}

void wait_for_input(void) {

	std::cin.get();
	if (std::cin.fail())
		std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void press_enter_to_continue(void) {

	std::cout << std::endl << "\e[5m" << "Press Enter to continue..." << reset;
	wait_for_input();
	std::cout << clear;
}
