/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rceschel <rceschel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 13:54:53 by rceschel          #+#    #+#             */
/*   Updated: 2025/12/16 16:29:48 by rceschel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ostream>

#define GET_LINE(input, str) {		\
	getline(input, str);			\
	if (input.eof())				\
		std::exit(EXIT_FAILURE);	\
}

std::ostream	&bold(std::ostream &os);
std::ostream	&red(std::ostream &os);
std::ostream	&green(std::ostream &os);
std::ostream	&blue(std::ostream &os);
std::ostream	&reset(std::ostream &os);
std::ostream	&clear(std::ostream &os);
std::string		itostr(int n);
void			clear_lines(std::ostream &os, int num_of_lines);
void			wait_for_input(void);
void			press_enter_to_continue(void);
