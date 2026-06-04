#include "Base.class.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>

Base::~Base() {};

static int uniformBoundedRand(int n = 3) {
	int	max = RAND_MAX - (RAND_MAX % n);
	int r = 0;

	do r = rand(); while (r >= max);
	return (r % n);
}

Base *	Base::generate( void ) {

	switch (uniformBoundedRand(3) + 1) {
		case 1:
			return new A();
		case 2:
			return new B();
		case 3:
			return new C();
		default:
			return NULL;
	}
}

void	Base::identify(Base *p) {

	if ( dynamic_cast<A*>(p) )
		std::cout << "A" << std::endl;
	else if ( dynamic_cast<B*>(p) )
		std::cout << "B" << std::endl;
	else if ( dynamic_cast<C*>(p) )
		std::cout << "C" << std::endl;
}

void	Base::identify(Base &p) {

	if ( dynamic_cast<A*>(&p) )
		std::cout << "A" << std::endl;
	else if ( dynamic_cast<B*>(&p) )
		std::cout << "B" << std::endl;
	else if ( dynamic_cast<C*>(&p) )
		std::cout << "C" << std::endl;
}
