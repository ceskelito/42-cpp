#include <iostream>
#include <ostream>
#include <string>
#include <fstream>

using std::string;
using std::ifstream;
using std::ofstream;

int substitute(ifstream &src, ofstream &tgt, const string s1, const string s2) {
	using std::getline;

	string				buff;
	string::size_type	prev = 0; 
	int					count = 0;
	
	getline(src, buff);

	for (string::size_type p = buff.find(s1); p != string::npos; p = buff.find(s1[prev])) {
		tgt << buff.substr(prev, p - 1);
		tgt << s2;
		prev = p + s2.length();
		if (p > buff.length())
			break ;
		count++;
	}
	tgt << buff.substr(prev, buff.length());
	
	// if (buff.find(s1) == string::npos)
	// 	std::cout << "POS: npos";
	// else
	// 	std::cout << "POS: " << buff.find(s1);
	return count;
}

int main(int ac, char **av) {

	if (ac != 4)
	{
		std::cout << "Usage: ./sed [input-file] <old_string> <new_string>" << std::endl;
		return (1);
	}

	const string	filename = av[1];
	const string	s1 = av[2];
	const string	s2 = av[3];
	ifstream		source;
	ofstream		target;

	source.open(filename.c_str());
	target.open((filename + ".replace").c_str());

	substitute(source, target, s1, s2);
}
