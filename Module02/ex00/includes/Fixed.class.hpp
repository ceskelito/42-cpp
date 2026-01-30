#pragma once

class Fixed {

private:
	int					_rawBits;
	static const int	_numFractional = 8;

public:
	Fixed(void);
	~Fixed(void);
	Fixed(const Fixed &other);
	Fixed &operator=(const Fixed &other);

	int		getRawBits(void) const;
	void	setRawBits(const int raw);
};
