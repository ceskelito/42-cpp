#include <iostream>
#include <ostream>
#include <string>
#include <fstream>

using std::string;
using std::ifstream;
using std::ofstream;

void	sed(ifstream &src, ofstream &tgt, const string s1, const string s2) {
	string				buff;
	string::size_type	pos = 0;
	bool				flag = false;
	
	
	while (getline(src, buff)) {
		if (flag)
			tgt << '\n';
		flag = true;
		while (pos = buff.find(s1), pos != string::npos) {
			tgt << buff.substr(0, pos) << s2;
			buff = buff.substr(pos + s1.length());
		}
		tgt << buff;
	}
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
	if (!source.is_open()) {
		std::cout << "Failed opening the file `" << filename << '\'' << std::endl;
		return (1);
	}
	target.open((filename + ".replace").c_str());
	sed(source, target, s1, s2);
}
