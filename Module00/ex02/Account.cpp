#include "Account.hpp"
#include <iostream>
#include <sstream>
#include <fstream>
#include <ctime>	// queste librearia e' di C: e' il modo giusto in c++?

using std::endl;

int Account::_nbAccounts = 0;
int Account::_totalAmount = 0;
int Account::_totalNbDeposits = 0;
int Account::_totalNbWithdrawals = 0;

static std::ofstream &get_logfile_stream(std::string filename) {

	static std::ofstream logfile_output_stream(filename);

	return logfile_output_stream;
}

void Account::_displayTimestamp(void) {

	static std::string		timestring;
	static std::ofstream	logfile;

	if (timestring.empty())
	{
		std::stringstream	ss;
		time_t				timestamp = time(NULL);
		struct tm			*t = localtime(&timestamp);

		ss <<
			t->tm_year + 1900	<<
			t->tm_mon + 1		<<
			t->tm_mday << '_'	<<
			t->tm_hour			<<
			t->tm_min			<<
			t->tm_sec;

		timestring = ss.str();
	}

	 get_logfile_stream(timestring + ".log") << '[' << timestring << ']';
}

Account::Account(int initial_deposit):

	_accountIndex(Account::_nbAccounts++),
	_amount(initial_deposit),
	_nbDeposits(0),
	_nbWithdrawals(0) {

	Account::_totalAmount += _amount;

	_displayTimestamp();
	get_logfile_stream(std::string()) << ' ' <<
			"index:"	<< _accountIndex	<< ";" <<
			"amount:"	<< _amount			<< ";" <<
			"created"	<< endl;
		
};

Account::~Account(void) {

	Account::_totalAmount -= _amount;

	_displayTimestamp();
	get_logfile_stream(std::string()) << ' ' <<
			"index:"	<< _accountIndex	<< ";" <<
			"amount:"	<< _amount			<< ";" <<
			"closed"	<< endl;
};


// ************************ //
// Static Members Functions //
// ************************ //

int Account::getNbAccounts(void) {
	return _nbAccounts;
}

int Account::getTotalAmount(void) {
	return _totalAmount;
}

int Account::getNbDeposits(void) {
	return _totalNbDeposits;
}

int Account::getNbWithdrawals(void) {
	return _totalNbWithdrawals;
}

void Account::displayAccountsInfos(void) {

	_displayTimestamp();
	get_logfile_stream(std::string()) << ' ' <<
			"accounts:"		<< _nbAccounts			<< ';' <<
			"total:"		<< _totalAmount			<< ';' <<
			"deposits:"		<< _totalNbDeposits		<< ';' <<
			"withdrawals:"	<< _totalNbWithdrawals	<< endl;

}

// ****************************** //
// Instances Relative's Functions //
// ****************************** //

void Account::makeDeposit(int deposit) {

	int		p_amount = _amount;

	_amount += deposit;
	_nbDeposits++;
	Account::_totalAmount += deposit;
	Account::_totalNbDeposits++;

	_displayTimestamp();
	get_logfile_stream(std::string()) << ' ' <<
		"index:"		<< _accountIndex	<< ';' <<
		"p_amount:"		<< p_amount			<< ';' <<
		"deposit:"		<< deposit			<< ';' <<
		"amount:"		<< _amount			<< ';' <<
		"nb_deposits:"	<< _nbDeposits		<< endl;
}

// Questa funzione evita le rindondanze ma si rende poco leggibile.
// Dovremmo forse accettare una duplicazione di codice se rende tutto più chiro?
bool Account::makeWithdrawal(int withdrawal) {

	int		p_amount = _amount;

	_displayTimestamp();

	if (withdrawal > _amount)
	{
		get_logfile_stream(std::string()) << ' ' <<
			"index:"		<< _accountIndex	<< ';' <<
			"p_amount:"		<< p_amount			<< ';' <<
			"withdrawal:"	<< "refused" << endl;
		return false;
	}

	_amount -= withdrawal;
	_nbWithdrawals++;
	Account::_totalAmount -= withdrawal;
	Account::_totalNbWithdrawals++;

	get_logfile_stream(std::string()) << ' '	<<
		"index:"			<< _accountIndex	<< ';' <<
		"p_amount:"			<< p_amount			<< ';' <<
		"withdrawal:"		<< withdrawal		<< ';' <<
		"amount:"			<< _amount			<< ';' <<
		"nb_withdrawals:"	<< _nbWithdrawals	<< endl;

	return true;
}

int Account::checkAmount(void) const {
	return _amount;
}

void Account::displayStatus(void) const {
	
	_displayTimestamp();
	get_logfile_stream(std::string()) << ' ' <<
		"index:"		<< _accountIndex	<< ';' <<
		"amount:"		<< _amount			<< ';' <<
		"deposits:"		<< _nbDeposits		<< ';' <<
		"withdrawals:"	<< _nbWithdrawals	<< endl;
}
