#include "BitcoinExchange.hpp"

#include <utility> // std::make_pair
#include <iostream>
#include <sstream>

#include <ctime>

// #include <string>
// #include <stdexcept>

BitcoinExchange::BitcoinExchange( std::string const & inputFile ):
	_priceDB(_parsePriceFile("data.csv")),
	_inputDB(_parseInputFile(inputFile)) {}

BitcoinExchange::~BitcoinExchange( void ) {}

std::string trim(const std::string& str)
{
    size_t	first = str.find_first_not_of(' ');
    if (std::string::npos == first)
        return str;
    size_t	last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}

bool BitcoinExchange::_dateIsValid(std::string date) {
    int		year, month, day;
    char	dash1, dash2;

	// Works beacuse istringstream save the data only if can fit the variable
    std::istringstream iss(date);
    iss >> year >> dash1 >> month >> dash2 >> day;

    if (date.length() != 10 || iss.fail() || dash1 != '-' || dash2 != '-' || !iss.eof()) {
        // throw std::invalid_argument("Invalide date format: " + date + ". Expected YYYY-MM-DD.");
		return false;
    }

    struct std::tm timeStruct = {};
	timeStruct.tm_year = year - 1900;
	timeStruct.tm_mon = month - 1;
	timeStruct.tm_mday = day;
	timeStruct.tm_isdst = -1;

	// Convert the struct in timestamp
    std::time_t timestamp = std::mktime(&timeStruct);

	// Obtain the normalized date string from the struct
    char buffer[11];
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d", &timeStruct);
    std::string normalizedDate(buffer);

    // If the normalized differs from the original, means that the date was Invalid
    if (timestamp == -1 || normalizedDate != date) {
        // throw std::invalid_argument("Invalid date: " + date);
		return false;
    }

    return true;
}

void	BitcoinExchange::printExchange() {

	t_database::iterator	inputIt = _inputDB.begin();

	while (inputIt != _inputDB.end()) {

		std::string			date = inputIt->first;
		float				amount = inputIt->second;
		std::ostringstream	output;

		if (!_dateIsValid(date)) {
			output << "Error: bad input => " << date;
		}
		else if (amount < 0) {
			output << "Error: not a positive number.";
		}
		else if (amount > 1000) {
			output << "Error: too large number.";
		}
		else {
			t_database::iterator	found = _priceDB.lower_bound(date);

			if (found == _priceDB.end()) {
				output << "Error: no data found for input => " << inputIt->first;
			}
			else {
				output << inputIt->first << " => " << inputIt->second * found->second; 
			}
		}
		std::cout << output.str() << std::endl;
		inputIt++;
	}
}

BitcoinExchange::t_database BitcoinExchange::_parsePriceFile(std::string const & priceFile) {
	return _parseFile<t_database>(priceFile, ',');
}

BitcoinExchange::t_unordered_database BitcoinExchange::_parseInputFile(std::string const & inputFile) {
	return _parseFile<t_unordered_database>(inputFile, '|');
}
