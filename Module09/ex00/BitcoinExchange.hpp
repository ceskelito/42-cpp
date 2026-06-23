#pragma once

#include <string>
#include <map>

template<typename _Tp>
	struct noCompare
    {
      bool
      operator()(const _Tp&, const _Tp&) const
      { return false; }
    };

class BitcoinExchange {

	private:
		typedef std::map <
			std::string,
			double,
			std::greater_equal<std::string>
			>
		t_btcValueDb;
		
		typedef std::multimap <
			std::string,
			double,
			noCompare<std::string>
			>
		t_inputQueryDb;

		t_btcValueDb	_priceDB;
		t_inputQueryDb	_inputDB;
	
		
		template <typename Database>
		Database		_parseFile(std::string const & filename, char const delimiter, std::string const & header);
		t_btcValueDb	_parsePriceFile(std::string const & priceFile);
		t_inputQueryDb	_parseInputFile(std::string const & inputFile);
		bool			_dateIsValid(std::string date);

		BitcoinExchange( void );

	public:
		BitcoinExchange( std::string const & inputFile );
		BitcoinExchange( BitcoinExchange const & other );
		~BitcoinExchange( void );
		BitcoinExchange& operator=( BitcoinExchange const & other);

		void	printExchange();
};

#include "BitcoinExchange.tpp"
