#include "Cat.class.hpp"

int main( void ) {
	Animal	*meta = new Animal();
	Cat		*cat = new Cat();

	cat->getType();
	cat->makeSound();
	meta->getType();
	meta->makeSound();

	Cat newCat = *cat;
	newCat.makeSound();

	delete cat;
	delete meta;
}
