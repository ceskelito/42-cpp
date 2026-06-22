#include "BitcoinExchange.hpp"

#include <utility> // std::make_pair
#include <iostream>
#include <sstream>

#include <cstdlib> // for strtod
#include <cerrno>  // for errno
#include <cstring> // for strerror
#include <ctime>

#include <fstream>
// #include <string>
// #include <stdexcept>

BitcoinExchange::BitcoinExchange( std::string const & inputFile ):
	_priceDB(_parsePriceFile("data.csv")),
	_inputDB(_parseInputFile(inputFile)) {}

BitcoinExchange::~BitcoinExchange( void ) {}

static std::string trim(const std::string& str)
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

BitcoinExchange::t_database	BitcoinExchange::_parseFile(std::string const & filename, char const delimiter) {

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
		key = trim(key);
		valueStr = trim(valueStr);
        char*	endPtr;
        errno = 0;
        float	value = strtof(valueStr.c_str(), &endPtr);
        if (errno != 0 || endPtr == valueStr.c_str()) {
            continue; // Skip lines with invalid numbers
        }

        res.insert(std::make_pair(key, value));
    }
    return res;
}

void	BitcoinExchange::printInfo() {

	t_database::reverse_iterator	inputIt = _inputDB.rbegin();
	std::ostringstream				output;

	while (inputIt != _inputDB.rend()) {

		std::string	date = inputIt->first;
		float		amount = inputIt->second;

		if (!_dateIsValid(date)) {
			output << "Error: bad input => " << date;
		}
		else if (amount < 0) {
			output << "Error: not a positive number.";
		}
		else {
			t_database::iterator	found = _priceDB.lower_bound(date);

			if (found == _priceDB.end()) {
				output << "Error: no data found for input => " << inputIt->first;
			}
			else {
				output << inputIt->first << " => " << inputIt->second << "*" << found->second; 
			}
		}
		std::cout << output.str() << std::endl;
		inputIt++;
	}
}

BitcoinExchange::t_database BitcoinExchange::_parsePriceFile(std::string const & priceFile) {
	return _parseFile(priceFile, ',');
}

BitcoinExchange::t_database BitcoinExchange::_parseInputFile(std::string const & inputFile) {
	return _parseFile(inputFile, '|');
}
