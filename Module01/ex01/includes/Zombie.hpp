/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rceschel <rceschel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 15:03:20 by rceschel          #+#    #+#             */
/*   Updated: 2025/12/23 15:21:58 by rceschel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>

class Zombie {

private:
	std::string	_name;
	
public:
	Zombie(std::string name);
	~Zombie(void);

	void	announce(void);
};

