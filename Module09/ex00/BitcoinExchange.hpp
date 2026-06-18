#pragma once

#include <fstream>
#include <string>
#include <map>

class BitcoinExchange {

	private:
		typedef std::multimap<std::string, double> t_database;

		// std::ifstream	_priceStream;
		// std::ifstream	_inputStream;	
		// std::string	_priceFile; //default: data.csv
		// std::string	_inputFile;
		t_database	_priceDB;
		t_database	_inputDB;
	
		// Stores the content of _dbFile (.csv) in _priceDB
		t_database	_parsePriceFile(std::string const & priceFile);
		t_database	_parseInputFile(std::string const & inputFile);

		BitcoinExchange( void );

	public:
		BitcoinExchange( std::string const & inputFile );
		BitcoinExchange( BitcoinExchange const & other );
		// [...] Other eventual constructors
		~BitcoinExchange( void );
		BitcoinExchange& operator=( BitcoinExchange const & other);
};
