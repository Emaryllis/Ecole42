#include "Cat.hpp"
#include <iostream>

Cat::Cat() : AAnimal("Cat"), brain(NULL) {
	brain = new Brain();
	std::cout << "Cat default constructor called" << std::endl;
}

Cat::Cat(const std::string& type) : AAnimal(type), brain(NULL) {
	brain = new Brain();
	std::cout << "Cat parameterized constructor called for " << this->getType() << std::endl;
}

Cat::Cat(const Cat& other) : AAnimal(other), brain(NULL) {
	brain = new Brain(*other.brain);
	std::cout << "Cat copy constructor called for " << this->getType() << std::endl;
}

Cat& Cat::operator=(const Cat& other) {
	if (this != &other) {
		AAnimal::operator=(other);
		if (brain)
			delete brain;
		brain = new Brain(*other.brain);
	}
	std::cout << "Cat copy assignment operator called for " << this->getType() << std::endl;
	return *this;
}

Cat::~Cat() {
	if (brain) {
		delete brain;
	}
	std::cout << "Cat destructor called for " << this->getType() << std::endl;
}

void Cat::makeSound() const {
	std::cout << "Meow!" << std::endl;
}

Brain* Cat::getBrain() const {
	return brain;
}
