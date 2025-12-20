#include "Account.hpp"
#include <iostream>
#include <strstream>
#include <fstream>
#include <ctime>

using std::cout;
using std::endl;

int Account::_nbAccounts = 0;
int Account::_totalAmount = 0;
int Account::_totalNbDeposits = 0;
int Account::_totalNbWithdrawals = 0;

static void	print_time(void) {
	
	time_t				timestamp = time(NULL);
	struct tm			*t = localtime(&timestamp);
	std::strstream		ss;

	ss << '[' <<
		t->tm_year + 1900	<<
		t->tm_mon + 1		<<
		t->tm_mday << '_'	<<
		t->tm_hour			<<
		t->tm_min			<<
		t->tm_sec			<<
		']' ;

	std::ofstream		log_file(ss.str());
	log_file << ss.str();
}

Account::Account(int initial_deposit):

	_accountIndex(Account::_nbAccounts++),
	_amount(initial_deposit),
	_nbDeposits(0),
	_nbWithdrawals(0) {

	Account::_totalAmount += _amount;

	print_time();
	cout << "index:"	<< _accountIndex	<< ";" <<
			"amount:"	<< _amount			<< ";" <<
			"created"	<< endl;
		
};

Account::~Account(void) {

	Account::_totalAmount -= _amount;

	print_time();
	cout << "index:"	<< _accountIndex	<< ";" <<
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

	print_time();
	cout << "accounts:"		<< _nbAccounts			<< ';' <<
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

	print_time();
	cout << "index:"		<< _accountIndex	<< ';' <<
			"p_amount:"		<< p_amount				<< ';' <<
			"deposit:"		<< deposit			<< ';' <<
			"amount:"		<< _amount			<< ';' <<
			"nb_deposits:"	<< _nbDeposits		<< endl;
}

bool Account::makeWithdrawal(int withdrawal) {

	int		p_amount = _amount;

	print_time();

	cout << "index:"		<< _accountIndex	<< ';' <<
			"p_amount:"		<< p_amount			<< ';';

	if (withdrawal > _amount)
	{
		cout << "withdrawal:refused" << endl;
		return false;
	}

	_amount -= withdrawal;
	_nbWithdrawals++;
	Account::_totalAmount -= withdrawal;
	Account::_totalNbWithdrawals++;

	cout << "withdrawal:"		<< withdrawal		<< ';' <<
			"amount:"			<< _amount			<< ';' <<
			"nb_withdrawals:"	<< _nbWithdrawals	<< endl;

	return true;
}

int Account::checkAmount(void) const {
	return _amount;
}

void Account::displayStatus(void) const {
	
	print_time();
	cout <<	"index:"		<< _accountIndex	<< ';' <<
			"amount:"		<< _amount			<< ';' <<
			"deposits:"		<< _nbDeposits		<< ';' <<
			"withdrawals:"	<< _nbWithdrawals	<< endl;
}
