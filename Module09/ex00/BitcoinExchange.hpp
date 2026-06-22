#pragma once

#include <fstream>
#include <string>
#include <map>

#include <cstdlib> // for strtod
#include <cerrno>  // for errno
#include <cstring> // for strerror

template<typename _Tp>
	struct noCompare : public std::binary_function<_Tp, _Tp, bool>
    {
      _GLIBCXX14_CONSTEXPR
      bool
      operator()(const _Tp&, const _Tp&) const
      { return false; }
    };

class BitcoinExchange {

	private:
		typedef std::multimap<std::string, double, std::greater_equal<std::string> >	t_database;
		typedef std::multimap<std::string, double, noCompare<std::string> >				t_unordered_database;

		t_database				_priceDB;
		t_unordered_database	_inputDB;
	
		
		template <typename Database>
		Database				_parseFile(std::string const & filename, char const delimiter, std::string const & header);
		t_database				_parsePriceFile(std::string const & priceFile);
		t_unordered_database	_parseInputFile(std::string const & inputFile);
		bool					_dateIsValid(std::string date);

		BitcoinExchange( void );

	public:
		BitcoinExchange( std::string const & inputFile );
		BitcoinExchange( BitcoinExchange const & other );
		~BitcoinExchange( void );
		BitcoinExchange& operator=( BitcoinExchange const & other);

		void	printExchange(); // Change name of this function
};

std::string trim(const std::string& str);

template <typename Database>
Database BitcoinExchange::_parseFile(std::string const & filename, char const delimiter, std::string const & header) {

	// TODO (?)
	// I maybe need to check for the spaces in between delimiter and words? For now is not relevant

    Database		res;
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
			valueStr = "nanf";
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
			continue;
        }
        res.insert(std::make_pair(key, value));
    }
    return res;
}

