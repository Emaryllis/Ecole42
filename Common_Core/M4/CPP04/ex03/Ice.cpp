#include "Ice.hpp"
#include <iostream>
#include "ICharacter.hpp"

Ice::Ice() : AMateria("Ice") {
	std::cout << "Ice Default constructor called" << std::endl;
}

Ice::Ice(Ice const& other) : AMateria(other) {
	std::cout << "Ice Copy constructor called for" << type << std::endl;
}

Ice& Ice::operator=(Ice const& other) {
	if (this != &other)
		AMateria::operator=(other);
	std::cout << "Ice Copy assignment operator called for" << type << std::endl;
	return *this;
}

Ice::~Ice() {
	std::cout << "Ice Destructor called for" << type << std::endl;
}

AMateria* Ice::clone() const {
	return new Ice(*this);
}

void Ice::use(ICharacter& target) {
	std::cout << "* shoots an ice bolt at " << target.getName() << " *" << std::endl;
}
