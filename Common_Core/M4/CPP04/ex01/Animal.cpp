#include "Animal.hpp"
#include <iostream>

Animal::Animal() : type("Animal") {
	std::cout << "Animal default constructor called" << std::endl;
}

Animal::Animal(const std::string& type) : type(type) {
	std::cout << "Animal parameterized constructor called for " << type << std::endl;
}

Animal::Animal(const Animal& other) : type(other.type) {
	std::cout << "Animal copy constructor called for " << type << std::endl;
}

Animal& Animal::operator=(const Animal& other) {
    if (this != &other) {
        type = other.type;
    }
	std::cout << "Animal copy assignment operator called for " << type << std::endl;
    return *this;
}

Animal::~Animal() {
	std::cout << "Animal destructor called for " << type << std::endl;
}

std::string Animal::getType() const {
    return type;
}

void Animal::makeSound() const {
    std::cout << "*insert animal sound here*" << std::endl;
}
