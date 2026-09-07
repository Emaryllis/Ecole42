#include "Cat.hpp"
#include <iostream>

Cat::Cat() : Animal("Cat"), brain(NULL) {
	brain = new Brain();
	std::cout << "Cat Default constructor called" << std::endl;
}

Cat::Cat(const std::string& type) : Animal(type), brain(NULL) {
	brain = new Brain();
	std::cout << "Cat Parameterized constructor called for " << this->getType() << std::endl;
}

Cat::Cat(const Cat& other) : Animal(other), brain(NULL) {
	brain = new Brain(*other.brain);
	std::cout << "Cat Copy constructor called for " << this->getType() << std::endl;
}

Cat& Cat::operator=(const Cat& other) {
	if (this != &other) {
		Animal::operator=(other);
		if (brain)
			delete brain;
		brain = new Brain(*other.brain);
	}
	std::cout << "Cat Copy assignment operator called for " << this->getType() << std::endl;
	return *this;
}

Cat::~Cat() {
	if (brain) {
		delete brain;
	}
	std::cout << "Cat Destructor called for " << this->getType() << std::endl;
}

void Cat::makeSound() const {
	std::cout << "Meow!" << std::endl;
}

Brain* Cat::getBrain() const {
	return brain;
}
