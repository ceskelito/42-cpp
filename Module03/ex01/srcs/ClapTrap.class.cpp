#include "ClapTrap.class.hpp"
#include <iostream>

using std::cout;
using std::endl;

// Constructors / Destructor

ClapTrap::ClapTrap(string name) : 
	_name(name),
	_hitPoints(10),
	_energyPoints(10),
	_attackDamage(0) {

	cout << "[ ClapTrap ] - " << _name << " has been born." << endl;
}

ClapTrap::~ClapTrap(void) {
	cout << "[ ClapTrap ] - " << _name << " has been destroyed." << endl;
}

ClapTrap::ClapTrap(const ClapTrap &other) :
	_name(other._name),
    _hitPoints(other._hitPoints),
    _energyPoints(other._energyPoints),
    _attackDamage(other._attackDamage) {

    cout << "[ ClapTrap ] - " << _name << " has been copied with copy constructor." << endl;
}

ClapTrap&   ClapTrap::operator=(const ClapTrap& other) {
    _name			= other._name;
    _hitPoints		= other._hitPoints;
    _energyPoints	= other._energyPoints;
    _attackDamage	= other._attackDamage;

    cout << "[ ClapTrap ] - " << _name << " has been copied with copy assignment operator." << endl;
    return (*this);
}

// Private Member Functions

void	ClapTrap::_subEnergy(unsigned int amount = 1) {
	_energyPoints -= amount;
}

void	ClapTrap::_subHit(unsigned int amount = 1) {
	_hitPoints -= amount;
}

void	ClapTrap::_gainEnergy(unsigned int amount = 1) {
	_energyPoints += amount;
}

void	ClapTrap::_gainHit(unsigned int amount = 1) {
	_hitPoints += amount;
}

// Public Member Functions

void    ClapTrap::attack( std::string const& target )
{
    if (_energyPoints <= 0)
    {
        cout << "[ ClapTrap ] - " << _name << " is out of energy! It cannot attack." << endl;
        return;
    }
    cout << "[ ClapTrap ] - " << _name << " attacks " << target << ", causing " << _attackDamage << " points of damage!" << endl;
	_subEnergy();
}

void    ClapTrap::takeDamage( unsigned int amount )
{
    cout << "[ ClapTrap ] - " << _name << " takes " << amount << " points of damage!" << endl;

    if (_hitPoints <= amount)
    {
        cout << "[ ClapTrap ] - " << _name << " is dead!" << endl;
		_subHit(_hitPoints);
        return;
    }
	_subHit(amount);
}

void    ClapTrap::beRepaired( unsigned int amount )
{
    if (_energyPoints < amount)
    {
        cout << "[ ClapTrap ] - " << _name << " is out of energy! It cannot be repaired." << endl;
        return;
    }
    cout << "[ ClapTrap ] - " << _name << " repairs itself, gaining " << amount << " hit points!" << endl;
	_subEnergy();
	_gainHit(amount);
}
