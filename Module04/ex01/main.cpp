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
	
	cout << endl;
	for (int i = 0; i < e_maxAnimals; i++) {
		cout << animals[i]->getType() << ": ";
		animals[i]->makeSound();
		cout << endl;
	}

	Animal *copies[e_maxAnimals];

	cout << "Creating copies of animals..." << endl;
	for (int i = 0; i < e_maxAnimals; i++) {
		copies[i] = new Animal(*animals[i]);
	}
	cout << endl;
	for (int i = 0; i < e_maxAnimals; i++){
		cout << "Index [" << i << "]" << endl;
		cout << "Original memory address: " << animals[i] << endl;
		cout << "Copy     memory address: " << copies[i] << endl;
		cout << endl;
	}

	cout << "Deliting originals..." << endl;
	for (int i = 0; i < e_maxAnimals; i++) {
		delete animals[i];
	}
	cout << endl;
	cout << "Deliting copies..." << endl;
	for (int i = 0; i < e_maxAnimals; i++) {
		delete copies[i];
	}
}
