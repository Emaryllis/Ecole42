#include "DiamondTrap.hpp"
#include <iostream>

DiamondTrap::DiamondTrap()
	: ClapTrap("DiamondTrap_clap_name"), FragTrap(), ScavTrap(), name("DiamondTrap") {
	hitPoints = 100;
	energyPoints = 50;
	attackDamage = 30;
	std::cout << "DiamondTrap default constructor called" << std::endl;
}

DiamondTrap::DiamondTrap(const std::string &name)
	: ClapTrap(name + "_clap_name"), FragTrap(name), ScavTrap(name), name(name) {
	hitPoints = 100;
	energyPoints = 50;
	attackDamage = 30;
	std::cout << "DiamondTrap parameterized constructor called for " << this->name << std::endl;
}

DiamondTrap::DiamondTrap(const DiamondTrap &other)
	: ClapTrap(static_cast<const ClapTrap &>(other)),
	  FragTrap(static_cast<const FragTrap &>(other)),
	  ScavTrap(static_cast<const ScavTrap &>(other)),
	  name(other.name) {
	std::cout << "DiamondTrap copy constructor called for " << name << std::endl;
}

DiamondTrap &DiamondTrap::operator=(const DiamondTrap &other) {
	if (this != &other) {
		ClapTrap::operator=(other);
		name = other.name;
	}
	std::cout << "DiamondTrap copy assignment operator called for " << name << std::endl;
	return *this;
}

DiamondTrap::~DiamondTrap() {
	std::cout << "DiamondTrap destructor called for " << name << std::endl;
}

void DiamondTrap::attack(const std::string &target) {
	ScavTrap::attack(target);
}

void DiamondTrap::whoAmI() const {
	std::cout << "DiamondTrap name: " << name << " | ClapTrap name: " << ClapTrap::name << std::endl;
}
