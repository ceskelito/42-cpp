#include "Cat.class.hpp"
#include "Dog.class.hpp"

#include <iostream>

using std::cout;
using std::endl;

enum { e_maxAnimals = 2 };

int main( void ) {

	Animal *animals[e_maxAnimals];

	if (e_maxAnimals % 2 != 0) {
		cout << "Please set a pair numer of animals" << endl;
		return 1;
	}

	for (int i = 0; i < e_maxAnimals; i++) {
		if (i % 2)
			animals[i] = new Cat();
		else 
			animals[i] = new Dog();
	}
	
	for (int i = 0; i < e_maxAnimals; i++) {
		cout << animals[i]->getType() << ": ";
		animals[i]->makeSound();
		cout << endl;
	}
}
