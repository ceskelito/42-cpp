#include <iostream>
#include <ostream>
#include <string>
#include <fstream>

#define GET_LINE(input, str) {		\
	getline(input, str);			\
	if (input.eof())				\
		std::exit(EXIT_FAILURE);	\
}

using std::string;

int main(int ac, char **av) {

	if (ac != 4)
	{
		std::cout << "Usage: ./sed [input-file] <old_string> <new_string>" << std::endl;
		return (1);
	}

	const string	filename = av[1];
	const string	s1 = av[2];
	const string	s2 = av[3];
	std::ifstream	source;
	std::ofstream	target;

	source.open(filename.c_str());
	target.open((filename + ".replace").c_str());

	// Di seguito la logica per l'estrazione
	// Modificare 'a' con la prima lettera di s1
	// Poi le solite iterazioni per sostituire
	//Potrebbe essere spostato in una funzione
	string	buff;

	std::getline(source, buff, 'a');
	std::cout << buff;
}
