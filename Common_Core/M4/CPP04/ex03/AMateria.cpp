#include "AMateria.hpp"
#include "ICharacter.hpp"
#include <iostream>

AMateria::AMateria() : type("AMateria") {
	std::cout << "AMateria default constructor called" << std::endl;
}

AMateria::AMateria(std::string const& type) : type(type) {
	std::cout << "AMateria parameterized constructor called for " << type << std::endl;
}

AMateria::AMateria(AMateria const& other) : type(other.type) {
	std::cout << "AMateria copy constructor called for " << type << std::endl;
}

AMateria& AMateria::operator=(AMateria const& other) {
	if (this != &other)
		type = other.type;
	std::cout << "AMateria copy assignment operator called for " << type << std::endl;
	return *this;
}

AMateria::~AMateria() {
	std::cout << "AMateria destructor called for " << type << std::endl;
}

std::string const& AMateria::getType() const {
	return type;
}

AMateria* AMateria::clone() const {
	return new AMateria(*this);
}

void AMateria::use(ICharacter&) {}
