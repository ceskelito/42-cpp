#pragma once

#include <fstream>
#include <string>
#include <map>

class BitcoinExchange {

	private:
		// Compare with std::greater in order to obtain the equal or nearest lower date when using lower_bound() method
		typedef std::multimap<std::string, double, std::greater<std::string> > t_database;

		t_database	_priceDB;
		t_database	_inputDB;
	
		// Stores the content of _dbFile (.csv) in _priceDB
		
		t_database	_parseFile(std::string const & filename, char const delimiter);
		t_database	_parsePriceFile(std::string const & priceFile);
		t_database	_parseInputFile(std::string const & inputFile);
		bool		_dateIsValid(std::string date);

		BitcoinExchange( void );

	public:
		BitcoinExchange( std::string const & inputFile );
		BitcoinExchange( BitcoinExchange const & other );
		~BitcoinExchange( void );
		BitcoinExchange& operator=( BitcoinExchange const & other);

		void	printInfo(); // Change name of this function
};
