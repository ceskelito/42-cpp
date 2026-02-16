#include "Cat.class.hpp"
#include "Dog.class.hpp"

#include <iostream>

int main( void ) {
	Animal	*meta = new Animal();
	Cat		*cat = new Cat();
	Dog		*dog = new Dog();

	cat->getType();
	cat->makeSound();
	std::cout << std::endl;
	meta->getType();
	meta->makeSound();
	std::cout << std::endl;
	dog->getType();
	dog->makeSound();

	delete cat;
	delete dog;
	delete meta;
}
