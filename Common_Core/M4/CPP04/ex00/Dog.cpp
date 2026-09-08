#include "Dog.hpp"
#include <iostream>

Dog::Dog() : Animal("Dog") {
	std::cout << "Dog default constructor called" << std::endl;
}

Dog::Dog(const std::string& type) : Animal(type) {
	std::cout << "Dog parameterized constructor called for " << this->getType() << std::endl;
}

Dog::Dog(const Dog& other) : Animal(other) {
	std::cout << "Dog copy constructor called for " << type << std::endl;
}

Dog& Dog::operator=(const Dog& other) {
	if (this != &other) {
		Animal::operator=(other);
		type = other.type;
	}
	std::cout << "Dog copy assignment operator called for " << type << std::endl;
	return *this;
}

Dog::~Dog() {
	std::cout << "Dog destructor called for " << type << std::endl;
}

void Dog::makeSound() const {
    std::cout << "Woof!" << std::endl;
}
