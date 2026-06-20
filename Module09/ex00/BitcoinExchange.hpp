#pragma once

#include <fstream>
#include <string>
#include <map>

class BitcoinExchange {

	private:
		typedef std::multimap<std::string, double> t_database;

		t_database	_priceDB;
		t_database	_inputDB;
	
		// Stores the content of _dbFile (.csv) in _priceDB
		t_database	_parsePriceFile(std::string const & priceFile);
		t_database	_parseInputFile(std::string const & inputFile);

		BitcoinExchange( void );

	public:
		BitcoinExchange( std::string const & inputFile );
		BitcoinExchange( BitcoinExchange const & other );
		~BitcoinExchange( void );
		BitcoinExchange& operator=( BitcoinExchange const & other);
};
