#include "Base.class.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>

int main()
{
	srand(std::time(0));

	Base *p1 = Base::generate(),
		 *p2 = Base::generate(),
		 *p3 = Base::generate(),
		 &r1 = *p1,
		 &r2 = *p2,
		 &r3 = *p3;


	std::cout << "Identifying pointers:" << std::endl;
	Base::identify(p1);
	Base::identify(p2);
	Base::identify(p3);

	std::cout << std::endl;

	std::cout << "Identifying references:" << std::endl;
	Base::identify(r1);
	Base::identify(r2);
	Base::identify(r3);

}
