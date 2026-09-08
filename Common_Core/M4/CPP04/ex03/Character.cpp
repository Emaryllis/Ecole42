#include "Character.hpp"

#include <iostream>
#include <ostream>

#include "AMateria.hpp"

Character::Character() : name("Character") {
	for (int i = 0; i < 4; ++i)
		inventory[i] = NULL;
	std::cout << "Character default constructor called" << std::endl;
}

Character::Character(std::string const& name) : name(name) {
	for (int i = 0; i < 4; ++i)
		inventory[i] = NULL;
	std::cout << "Character parameterized constructor called for " << name << std::endl;
}

Character::Character(Character const& other) : name(other.name) {
	for (int i = 0; i < 4; ++i)
		inventory[i] = NULL;
	copyInventory(other);
	std::cout << "Character copy constructor called for " << name << std::endl;
}

Character& Character::operator=(Character const& other) {
	if (this != &other) {
		clearInventory();
		name = other.name;
		copyInventory(other);
	}
	std::cout << "Character copy assignment operator called for " << name << std::endl;
	return *this;
}

Character::~Character() {
	clearInventory();
	std::cout << "Character destructor called for " << name << std::endl;
}

std::string const& Character::getName() const {
	return name;
}

void Character::equip(AMateria* m) {
	if (!m)
		return;
	for (int i = 0; i < 4; ++i) {
		if (inventory[i] == NULL) {
			inventory[i] = m;
			return;
		}
	}
}

void Character::unequip(int idx) {
	if (idx < 0 || idx >= 4)
		return;
	inventory[idx] = NULL;
}

void Character::use(int idx, ICharacter& target) {
	if (idx < 0 || idx >= 4)
		return;
	if (inventory[idx])
		inventory[idx]->use(target);
}

void Character::clearInventory() {
	for (int i = 0; i < 4; ++i) {
		if (inventory[i]) {
			delete inventory[i];
			inventory[i] = NULL;
		}
	}
}

void Character::copyInventory(Character const& other) {
	for (int i = 0; i < 4; ++i) {
		if (other.inventory[i])
			inventory[i] = other.inventory[i]->clone();
		else
			inventory[i] = NULL;
	}
}
