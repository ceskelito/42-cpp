#pragma once

#include <string>

class Brain {

private:
	enum { _maxIdeas = 100 };
	
	Brain& operator=(Brain &other);
	
	void	_announceMethod(std::string methodName);

protected:
	std::string	ideas[_maxIdeas];

public:
	Brain( void );
	~Brain( void );
	Brain( Brain &other );
};
