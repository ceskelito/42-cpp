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
	std::ostream &operator<<(std::ostream &os);
	~Fixed(void);

	int		getRawBits(void) const;
	void	setRawBits(const int raw);
	int		toInt(void);
	float	toFloat(void);
};
