#include "Cat.hpp"
#include <iostream>

Cat::Cat() : Animal("Cat") {
	std::cout << "Cat default constructor called" << std::endl;
}

Cat::Cat(const std::string& type) : Animal(type) {
	std::cout << "Cat parameterized constructor called for " << this->getType() << std::endl;
}

Cat::Cat(const Cat& other) : Animal(other) {
	std::cout << "Cat copy constructor called for " << type << std::endl;
}

Cat& Cat::operator=(const Cat& other) {
	if (this != &other) {
		Animal::operator=(other);
		type = other.type;
	}
	std::cout << "Cat copy assignment operator called for " << type << std::endl;
    return *this;
}

Cat::~Cat() {
	std::cout << "Cat destructor called for " << type << std::endl;
}

void Cat::makeSound() const {
    std::cout << "Meow!" << std::endl;
}
