#include "Cat.class.hpp"
#include "Dog.class.hpp"

#include "WrongCat.class.hpp"
#include "WrongDog.class.hpp"

#include <iostream>

int main( void ) {
	std::cout << "Correct Animals test suite..." << std::endl << std::endl;

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

	std::cout << std::endl << "#####################################" << std::endl << std::endl;
	std::cout << "Wrong Animals test suite..." << std::endl << std::endl;

	WrongAnimal	*w_meta = new WrongAnimal();
	WrongAnimal	*w_cat = new WrongCat();
	WrongAnimal	*w_dog = new WrongDog();

	std::cout << std::endl;
	
	w_cat->getType();
	w_cat->makeSound();

	std::cout << std::endl;

	w_meta->getType();
	w_meta->makeSound();

	std::cout << std::endl;

	w_dog->getType();
	w_dog->makeSound();
	
	std::cout << std::endl;

	delete w_cat;
	delete w_dog;
	delete w_meta;
}
