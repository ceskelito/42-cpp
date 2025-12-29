#include <iostream>
#include <iomanip>

using std::cout;
using std::endl;
using std::setw;
using std::string;

std::ostream &bold(std::ostream &os) {
        return os << "\e[1m";
}

std::ostream &reset(std::ostream &os) {
        return os << "\e[0m";
}

int main(void) {

	const int		w = 16;
	const string	stringVAR = "HI THIS IS BRAIN";
	const string	*stringPTR = &stringVAR;
	const string	&stringREF = stringVAR;

	cout << bold << std::left << 
		setw(w - 6) << "Element"	<< setw(w)	<< "Address"	<< setw(w)	<< "Value"		<< endl << reset <<
		setw(w - 6) << "Variable"	<< setw(w)	<< &stringVAR	<< setw(w)	<< stringVAR	<< endl <<
		setw(w - 6) << "Pointer"	<< setw(w)	<< stringPTR	<< setw(w)	<< *stringPTR	<< endl <<
		setw(w - 6) << "Reference"	<< setw(w)	<< &stringREF	<< setw(w)	<< stringREF	<< endl;

}
