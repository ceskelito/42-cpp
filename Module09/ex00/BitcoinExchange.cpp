#include "BitcoinExchange.hpp"

#include <limits.h>

typedef std::multimap<std::string, double> t_database;

BitcoinExchange::BitcoinExchange( std::string const & inputFile ):
	_priceDB(_parsePriceFile("data.csv")),
	_inputDB(_parseInputFile(inputFile))
{};

static std::ifstream openFile(std::string const & fileName) {

	std::ifstream	file;

	file.exceptions( std::ifstream::badbit );
	file.open(fileName);
	return file;
}

static t_database parseFile(std::string const & fileName, char const & delimiter) {

	t_database		res;
	std::ifstream	file;
	char			line[INT_MAX];
	std::string		s;
	std::string		key;
	double			value;

	file.exceptions( std::ifstream::badbit );
	file.open(fileName);

	while ( file.getline(line, INT_MAX - 1, '\n') ) {
		s = line;
		key = s.substr(0, s.find_first_of(delimiter) - 1);
		value = std::strtod(s.substr(s.find_first_of(delimiter) + 1).c_str(), NULL);
		// TODO Check errors from strtod
		res.insert({key, value});
	}
	return res;
}

BitcoinExchange::t_database BitcoinExchange::_parsePriceFile(std::string const & priceFile) {
	return parseFile(priceFile, ',');
}

BitcoinExchange::t_database BitcoinExchange::_parseInputFile(std::string const & inputFile) {
	return parseFile(inputFile, '|');
}
