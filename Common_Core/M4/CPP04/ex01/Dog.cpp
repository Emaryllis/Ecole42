#include "Dog.hpp"
#include <iostream>

Dog::Dog() : Animal("Dog"), brain(NULL) {
	brain = new Brain();
	std::cout << "Dog Default constructor called" << std::endl;
}

Dog::Dog(const std::string& type) : Animal(type), brain(NULL) {
	brain = new Brain();
	std::cout << "Dog Parameterized constructor called for " << this->getType() << std::endl;
}

Dog::Dog(const Dog& other) : Animal(other), brain(NULL) {
	brain = new Brain(*other.brain);
	std::cout << "Dog Copy constructor called for " << this->getType() << std::endl;
}

Dog& Dog::operator=(const Dog& other) {
	if (this != &other) {
		Animal::operator=(other);
		if (brain)
			delete brain;
		brain = new Brain(*other.brain);
	}
	std::cout << "Dog Copy assignment operator called for " << this->getType() << std::endl;
	return *this;
}

Dog::~Dog() {
	if (brain) {
		delete brain;
	}
	std::cout << "Dog Destructor called for " << this->getType() << std::endl;
}

void Dog::makeSound() const {
	std::cout << "Woof!" << std::endl;
}

Brain* Dog::getBrain() const {
	return brain;
}
