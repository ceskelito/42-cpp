#include "Bureaucrat.class.hpp"
#include "ShrubberyCreationForm.class.hpp"
#include "AnsiColorCodes.h"
#include <iostream>

using std::cout;
using std::endl;

struct HeaderManip {
    std::ostream& apply(std::ostream& os) const {
        os << BLK << WHTB;
        return os;
    }
};

// Proxy che cattura il testo successivo e aggiunge il reset
struct HeaderProxy {
    std::ostream& os;

    HeaderProxy(std::ostream& os) : os(os) {}

    // Cattura qualsiasi valore, lo stampa colorato, poi resetta
    template <typename T>
    std::ostream& operator<<(const T& val) {
        os << val << CRESET;
        return os;
    }
};

// operator<< tra ostream e HeaderManip → restituisce HeaderProxy
HeaderProxy operator<<(std::ostream& os, const HeaderManip&) {
    os << BLK << WHTB;
    return HeaderProxy(os);
}

HeaderManip header() {
    return HeaderManip();
}

int main(void)
{
	cout << header() << "Creating a Form:" <<  endl;
	ShrubberyCreationForm	first("BeatifulTree");
	cout << endl;

	cout << header() << "Creating a copy from the first Form:" << endl;
	ShrubberyCreationForm	second(first);
	cout << endl;

	cout << header() << "Creating a Bureaucrat:" << endl;
	Bureaucrat				b("Bobby", 10);
	cout << endl;

	cout << header() << "Executing some Forms..." << endl;
	first.execute(b);
	return 0;
}
