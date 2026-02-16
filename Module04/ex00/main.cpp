#include "Cat.class.hpp"
#include "Dog.class.hpp"

#include <iostream>

int main( void ) {
	Animal	*meta = new Animal();
	Animal	*cat = new Cat();
	Animal	*dog = new Dog();

	std::cout << std::endl;
	
	cat->getType();
	cat->makeSound();

	std::cout << std::endl;

	meta->getType();
	meta->makeSound();

	std::cout << std::endl;

	dog->getType();
	dog->makeSound();
	
	std::cout << std::endl;

	delete cat;
	delete dog;
	delete meta;
}
