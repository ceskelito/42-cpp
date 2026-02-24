#include "Cat.class.hpp"
#include "Dog.class.hpp"

#include <iostream>

using std::cout;
using std::endl;

enum { e_maxAAnimals = 2 };

int main( void ) {

	AAnimal *animals[e_maxAAnimals];

	cout << "Constructing animals..." << endl;
	cout << "- - - - - -" << endl;
	for (int i = 0; i < e_maxAAnimals; i++) {
		if (i % 2)
			animals[i] = new Cat();
		else 
			animals[i] = new Dog();
		cout << "- - - - - -" << endl;
	}
	cout << endl;

	cout << "Let's listen the animals sounds..." << endl;
	cout << "- - - - - -";
	for (int i = 0; i < e_maxAAnimals; i++) {
		cout << endl;
		cout << animals[i]->getType() << ": ";
		animals[i]->makeSound();
	}
	cout << "- - - - - -" << endl << endl;

	AAnimal *copies[e_maxAAnimals];

	cout << "Creating copies of animals..." << endl;
	cout << "- - - - - -" << endl;
	for (int i = 0; i < e_maxAAnimals; i++){
		copies[i] = animals[i]->clone();
		cout << "- - - - - -" << endl;
	}
	cout << endl;

	cout << "Demostrating that copies are deep copies..." << endl;
	cout << "- - - - - -";
	for (int i = 0; i < e_maxAAnimals; i++){
		cout << endl;
		cout << "Index [" << i << "]" << endl;
		cout << "Original memory address: " << animals[i] << endl;
		cout << "  Copy   memory address: " << copies[i] << endl;
	}
	cout << "- - - - - -" << endl << endl;

	cout << "Deliting originals..." << endl;
	cout << "- - - - - -" << endl;
	for (int i = 0; i < e_maxAAnimals; i++) {
		delete animals[i];
		cout << "- - - - - -" << endl;
	}
	cout << endl;

	cout << "Deliting copies..." << endl;
	cout << "- - - - - -" << endl;
	for (int i = 0; i < e_maxAAnimals; i++) {
		delete copies[i];
		cout << "- - - - - -" << endl;
	}
}
