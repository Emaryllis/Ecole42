#include "Animal.hpp"
#include <iostream>

AAnimal::AAnimal() : type("AAnimal") {
	std::cout << "AAnimal Default constructor called" << std::endl;
}

AAnimal::AAnimal(const std::string& type) : type(type) {
	std::cout << "AAnimal Parameterized constructor called for " << type << std::endl;
}

AAnimal::AAnimal(const AAnimal& other) : type(other.type) {
	std::cout << "AAnimal Copy constructor called for " << type << std::endl;
}

AAnimal& AAnimal::operator=(const AAnimal& other) {
    if (this != &other) {
        type = other.type;
    }
	std::cout << "AAnimal Copy assignment operator called for " << type << std::endl;
    return *this;
}

AAnimal::~AAnimal() {
	std::cout << "AAnimal Destructor called for " << type << std::endl;
}

std::string AAnimal::getType() const {
    return type;
}
