#pragma once

#include "BitcoinExchange.hpp"

#include <fstream>
#include <cstdlib> // for strtod
#include <cerrno>  // for errno
#include <cstring> // for strerror

std::string trim(const std::string& str);

template <typename Database>
Database BitcoinExchange::_parseFile(std::string const & filename, char const delimiter, std::string const & header) {

    Database		ret;
    std::ifstream	file(filename.c_str());

    if (!file.is_open())
        throw std::runtime_error("Failed to open file: " + filename);

    std::string	line;

	std::getline(file, line);
	if (trim(line) != header)
		throw std::invalid_argument("Invalid header in file " + filename + ". Expected: `" + header + "'");

    while (std::getline(file, line)) {
        size_t delimiterPos = line.find_first_of(delimiter);
		std::string	key;
		std::string valueStr;

		if (delimiterPos == std::string::npos) {
			key = line;
			valueStr = "nan";
        } else {
			key = line.substr(0, delimiterPos);
			valueStr = line.substr(delimiterPos + 1);
		}
		key = trim(key);
		valueStr = trim(valueStr);
        errno = 0;
        char	*endPtr;
        float	value = strtof(valueStr.c_str(), &endPtr);
        if (errno != 0 || endPtr == valueStr.c_str()) {
			value = strtof("nan", NULL);
		}
        ret.insert(std::make_pair(key, value));
    }
    return ret;
}

