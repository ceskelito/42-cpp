#include "Account.hpp"
#include <iostream>
#include <ctime>

using std::cout;
using std::endl;

int Account::_nbAccounts = 0;
int Account::_totalAmount = 0;
int Account::_totalNbDeposits = 0;
int Account::_totalNbWithdrawals = 0;

Account::Account(int initial_deposit):

	_accountIndex(Account::_nbAccounts++),
	_amount(initial_deposit),
	_nbDeposits(0),
	_nbWithdrawals(0) {

	time_t	timestamp;

	_totalAmount += _amount;

	time(&timestamp);
	
	cout << '[' << timestamp << "] " <<
		"index:"	<< _accountIndex	<< ";" <<
		"amount:"	<< _amount			<< ";" <<
		"created"	<< endl;
		
};

Account::~Account(void) {
	time_t	timestamp;

	_totalAmount -= _amount;

	time(&timestamp);
	
	cout << '[' << timestamp << "] " <<
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

	time_t	timestamp;

	time(&timestamp);
	cout << '[' << timestamp << "] " <<
		"accounts:"		<< _nbAccounts			<< ';' <<
		"total:"		<< _totalAmount			<< ';' <<
		"deposits:"		<< _totalNbDeposits		<< ';' <<
		"withdrawals:"	<< _totalNbWithdrawals	<< endl;

}

// ****************************** //
// Instances Relative's Functions //
// ****************************** //

void Account::makeDeposit(int deposit) {

	int	p_am = _amount;
	time_t	timestamp;

	this->_amount += deposit;
	this->_nbDeposits++;
	Account::_totalAmount += deposit;
	Account::_totalNbDeposits++;

	time(&timestamp);
	cout << '[' << timestamp << "] " <<
		"index:"		<< _accountindex		<< ';' <<
		"accounts:"		<< _nbAccounts			<< ';' <<
		"total:"		<< _totalAmount			<< ';' <<
		"deposits:"		<< _totalNbDeposits		<< ';' <<
		"withdrawals:"	<< _totalNbWithdrawals	<< endl;

}

bool Account::makeWithdrawal(int withdrawal) {

	if (withdrawal > this->_amount)
		return false;

	this->_amount -= withdrawal;
	this->_nbWithdrawals++;
	Account::_totalAmount -= withdrawal;
	Account::_totalNbWithdrawals++;

	return true;
}

int Account::checkAmount(void) const {
	return _amount;
}

void Account::displayStatus(void) const {
	time_t	timestamp;

	time(&timestamp);
	
	cout << '[' << timestamp << "] " <<
		"index:"		<< _accountIndex	<< ';' <<
		"amount:"		<< _amount			<< ';' <<
		"deposits:"		<< _nbDeposits		<< ';' <<
		"withdrawals:"	<< _nbWithdrawals	<< endl;
}
