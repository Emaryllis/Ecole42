#include "Cure.hpp"
#include <iostream>
#include "ICharacter.hpp"

Cure::Cure() : AMateria("Cure") {
	std::cout << "Cure Default constructor called" << std::endl;
}

Cure::Cure(Cure const& other) : AMateria(other) {
	std::cout << "Cure Copy constructor called for " << type << std::endl;
}

Cure& Cure::operator=(Cure const& other) {
	if (this != &other)
		AMateria::operator=(other);
	std::cout << "Cure Copy assignment operator called for " << type << std::endl;
	return *this;
}

Cure::~Cure() {
	std::cout << "Cure Destructor called for " << type << std::endl;
}

AMateria* Cure::clone() const {
	return new Cure(*this);
}

void Cure::use(ICharacter& target) {
	std::cout << "* heals " << target.getName() << "'s wounds *" << std::endl;
}
