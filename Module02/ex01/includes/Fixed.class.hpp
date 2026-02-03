#pragma once

#include <ostream>

class Fixed {

private:
	int					_rawBits;
	static const int	_numFractional = 8;

public:
	Fixed(void);
	Fixed(const Fixed &other);
	Fixed(const int value);
	Fixed(const float value);
	Fixed &operator=(const Fixed &other);
	~Fixed(void);

	int		getRawBits(void) const;
	void	setRawBits(const int raw);
	int		toInt(void) const;
	float	toFloat(void) const;
};
	
std::ostream &operator<<(std::ostream &os, const Fixed &f);
