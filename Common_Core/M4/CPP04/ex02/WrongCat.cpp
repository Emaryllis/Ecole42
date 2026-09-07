#include "WrongCat.hpp"
#include <iostream>

WrongCat::WrongCat() : WrongAnimal("WrongCat") {
	std::cout << "WrongCat default constructor called" << std::endl;
}

WrongCat::WrongCat(const std::string& type) : WrongAnimal(type) {
	std::cout << "WrongCat parameterized constructor called for " << type << std::endl;
}

WrongCat::WrongCat(const WrongCat& other) : WrongAnimal(other) {
	std::cout << "WrongCat copy constructor called" << std::endl;
}

WrongCat& WrongCat::operator=(const WrongCat& other) {
	if (this != &other) {
		WrongAnimal::operator=(other);
		type = other.type;
	}
	std::cout << "WrongCat Copy assignment operator called for " << type << std::endl;
    return *this;
}

WrongCat::~WrongCat() {
	std::cout << "WrongCat Destructor called for " << type << std::endl;
}
