#include "Dog.hpp"
#include <iostream>

Dog::Dog() : Animal("Dog") {
	std::cout << "Dog Default constructor called" << std::endl;
}

Dog::Dog(const std::string& type) : Animal(type) {
	std::cout << "Dog Parameterized constructor called for " << this->getType() << std::endl;
}

Dog::Dog(const Dog& other) : Animal(other) {
	std::cout << "Dog Copy constructor called for " << type << std::endl;
}

Dog& Dog::operator=(const Dog& other) {
	if (this != &other) {
		Animal::operator=(other);
		type = other.type;
	}
	std::cout << "Dog Copy assignment operator called for " << type << std::endl;
	return *this;
}

Dog::~Dog() {
	std::cout << "Dog Destructor called for " << type << std::endl;
}

void Dog::makeSound() const {
    std::cout << "Woof!" << std::endl;
}
