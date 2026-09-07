#include "Animal.hpp"
#include <iostream>

Animal::Animal() : type("Animal") {
	std::cout << "Animal Default constructor called" << std::endl;
}

Animal::Animal(const std::string& type) : type(type) {
	std::cout << "Animal Parameterized constructor called for " << type << std::endl;
}

Animal::Animal(const Animal& other) : type(other.type) {
	std::cout << "Animal Copy constructor called for " << type << std::endl;
}

Animal& Animal::operator=(const Animal& other) {
    if (this != &other) {
        type = other.type;
    }
	std::cout << "Animal Copy assignment operator called for " << type << std::endl;
    return *this;
}

Animal::~Animal() {
	std::cout << "Animal Destructor called for " << type << std::endl;
}

std::string Animal::getType() const {
    return type;
}

void Animal::makeSound() const {
    std::cout << "*insert animal sound here*" << std::endl;
}
