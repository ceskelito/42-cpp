#include "BitcoinExchange.hpp"

#include <iostream>
#include <sstream>
#include <utility> // std::make_pair
#include <ctime> // Date validation

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

	// Declare variables for date components and create the input stream.
	// This variable will be used to fill the time Struct
    int					year, month, day;
    char				dash[2];
    std::istringstream	iss(date);

	// istringstream extracts values by matching their declared types
    iss >> year >> dash[0] >> month >> dash[1] >> day;

    if (date.length() != 10 || iss.fail() || dash[0] != '-' || dash[1] != '-' || !iss.eof()) {
		return false;
    }

    struct std::tm timeStruct = {};
	timeStruct.tm_year = year - 1900;
	timeStruct.tm_mon = month - 1;
	timeStruct.tm_mday = day;
	timeStruct.tm_isdst = -1;

	// Obtain the date's timestamp, used in later checks
    std::time_t timestamp = std::mktime(&timeStruct);

	// Convert the tm struct to a string with the format YYYY-mm-dd.
	// If a date is invalid, mktime/strftime will approximate it to a valid date.
    char normalizedDate[11];
    std::strftime(normalizedDate, sizeof(normalizedDate), "%Y-%m-%d", &timeStruct);

    // If the normalized date differs from the original, or if mktime failed,
	// the date is invalid
    if (timestamp == -1 || date != std::string(normalizedDate)) {
		return false;
	}

    return true;
}

void	BitcoinExchange::printExchange() {

	t_btcValueDb::iterator	inputIt = _inputDB.begin();

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
		// nan
		else if (amount != amount) {
			output << "Error: not a number.";
		}
		else {
			t_btcValueDb::iterator	found = _priceDB.lower_bound(date);

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

BitcoinExchange::t_btcValueDb BitcoinExchange::_parsePriceFile(std::string const & priceFile) {
	return _parseFile<t_btcValueDb>(priceFile, ',', "date,exchange_rate");
}

BitcoinExchange::t_inputQueryDb BitcoinExchange::_parseInputFile(std::string const & inputFile) {
	return _parseFile<t_inputQueryDb>(inputFile, '|', "date | value");
}
