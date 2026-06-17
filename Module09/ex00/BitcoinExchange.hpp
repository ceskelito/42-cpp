#pragma once

// #include <fstream>
#include <string>
#include <map>

class BitcoinExchange {

	private:
		typedef std::multimap<std::string, double> t_database;

		t_database	_priceDB;
		t_database	_inputDB;
		std::string	_priceFile; //default: data.csv
		std::string	_inputFile;
	
		// Stores the content of _dbFile (.csv) in _priceDB
		void		parseCsvFile();
		void		parseInputFile();

	public:
		BitcoinExchange( void );
		BitcoinExchange( BitcoinExchange const & other );
		BitcoinExchange( std::string const & inputFile );
		// [...] Other eventual constructors
		~BitcoinExchange( void );
		BitcoinExchange& operator=( BitcoinExchange const & other);
};
