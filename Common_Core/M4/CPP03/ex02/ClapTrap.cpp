#include "ClapTrap.hpp"
#include <iostream>

ClapTrap::ClapTrap() : name("ClapTrap"), hitPoints(10), energyPoints(10), attackDamage(0) {
	std::cout << "ClapTrap default constructor called" << std::endl;
}

ClapTrap::ClapTrap(const std::string &name) : name(name), hitPoints(10), energyPoints(10), attackDamage(0) {
	std::cout << "ClapTrap parameterized constructor called for " << this->name << std::endl;
}

ClapTrap::~ClapTrap() {
	std::cout << "ClapTrap destructor called for " << name << std::endl;
}

ClapTrap::ClapTrap(const ClapTrap &obj)
	: name(obj.name), hitPoints(obj.hitPoints), energyPoints(obj.energyPoints), attackDamage(obj.attackDamage) {
	std::cout << "ClapTrap copy constructor called for " << name << std::endl;
}

ClapTrap &ClapTrap::operator=(const ClapTrap &other) {
	if (this != &other) {
		name = other.name;
		hitPoints = other.hitPoints;
		energyPoints = other.energyPoints;
		attackDamage = other.attackDamage;
	}
	std::cout << "ClapTrap copy assignment operator called for " << name << std::endl;
	return *this;
}

void ClapTrap::attack(const std::string &target) {
	if (hitPoints == 0) {
		std::cout << "ClapTrap " << name << " cannot attack because it has no hit points left." << std::endl;
		return;
	}
	if (energyPoints == 0) {
		std::cout << "ClapTrap " << name << " cannot attack because it has no energy points left." << std::endl;
		return;
	}
	std::cout << "ClapTrap " << name << " attacks " << target << ", causing " << attackDamage << " points of damage!" << std::endl;
	energyPoints--;
}

void ClapTrap::takeDamage(unsigned int amount) {
	if (hitPoints == 0) {
		std::cout << "ClapTrap " << name << " is already destroyed." << std::endl;
		return;
	}
	if (amount >= hitPoints)
		hitPoints = 0;
	else
		hitPoints -= amount;
	std::cout << "ClapTrap " << name << " takes " << amount << " points of damage! Current hit points: " << hitPoints << std::endl;
}

void ClapTrap::beRepaired(unsigned int amount) {
	if (hitPoints == 0) {
		std::cout << "ClapTrap " << name << " cannot repair because it has no hit points left." << std::endl;
		return;
	}
	if (energyPoints == 0) {
		std::cout << "ClapTrap " << name << " cannot repair because it has no energy points left." << std::endl;
		return;
	}
	hitPoints += amount;
	energyPoints--;
	std::cout << "ClapTrap " << name << " is repaired by " << amount << " points! Current hit points: " << hitPoints << std::endl;
}
