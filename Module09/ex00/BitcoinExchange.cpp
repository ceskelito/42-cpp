#include "BitcoinExchange.hpp"

#include <cstdlib>
#include <limits.h>
#include <utility> // std::make_pair

typedef std::multimap<std::string, double> t_database;

BitcoinExchange::BitcoinExchange( std::string const & inputFile ):
	_priceDB(_parsePriceFile("data.csv")),
	_inputDB(_parseInputFile(inputFile)) {}

BitcoinExchange::~BitcoinExchange( void ) {}

#include <fstream>
#include <string>
#include <cstdlib> // for strtod
#include <cerrno>  // for errno
#include <cstring> // for strerror
#include <stdexcept>

/* TODO
 * Check the date format and value validity
 * Check the btc amount in input validity
 * Coerhently manage errors and choose how
 */

static std::string trim(const std::string& str)
{
    size_t	first = str.find_first_not_of(' ');
    if (std::string::npos == first)
        return str;
    size_t	last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}

static t_database parseFile(std::string const & filename, char const delimiter) {

    t_database		res;
    std::ifstream	file(filename.c_str());

    if (!file.is_open())
        throw std::runtime_error(("Failed to open file: " + filename).c_str());

    std::string	line;
    while (std::getline(file, line)) {
        size_t delimiterPos = line.find_first_of(delimiter);
		std::string	key;
		std::string valueStr;

		if (delimiterPos == std::string::npos) {
			key = line;
			valueStr = "";
        } else {
			key = line.substr(0, delimiterPos);
			valueStr = line.substr(delimiterPos + 1);
		}

        char*	endPtr;
        errno = 0;
        double	value = strtod(valueStr.c_str(), &endPtr);
        if (errno != 0 || endPtr == valueStr.c_str()) {
            continue; // Skip lines with invalid numbers
        }

        res.insert(std::make_pair(trim(key), value));
    }
    return res;
}

#include <iostream>
void	BitcoinExchange::printInfo() {

	t_database::iterator	it = _inputDB.begin();
	t_database::iterator	found = _priceDB.end();

	while (it != _inputDB.end()) {
		found = _priceDB.find(it->first);
		if (found == _priceDB.end())
		{
			// Logic to find the nearest lower number
			std::cout << it->first << " NOT FOUND - i'll find the nearest..." <<  std::endl;
			it++;
			continue;
		}
		std::cout << it->first << " => " << it->second * found->second << std::endl;
		it++;
	}
}

//.///.//.///

// static t_database parseFile(std::string const & fileName, char const delimiter) {
//
// 	t_database		res;
// 	std::ifstream	file;
// 	char			line[INT_MAX];
// 	std::string		s;
// 	std::string		key;
// 	double			value;
//
// 	file.exceptions( std::ifstream::badbit );
// 	file.open(fileName.c_str());
//
// 	while ( file.getline(line, INT_MAX - 1, '\n') ) {
// 		s = line;
// 		key = s.substr(0, s.find_first_of(delimiter) - 1);
// 		value = strtod(s.substr(s.find_first_of(delimiter) + 1).c_str(), NULL);
// 		// TODO Check errors from strtod
// 		res.insert(std::make_pair(key, value));
// 	}
// 	return res;
// }

BitcoinExchange::t_database BitcoinExchange::_parsePriceFile(std::string const & priceFile) {
	char const d = ',';
	return parseFile(priceFile, d);
}

BitcoinExchange::t_database BitcoinExchange::_parseInputFile(std::string const & inputFile) {
	return parseFile(inputFile, '|');
}
