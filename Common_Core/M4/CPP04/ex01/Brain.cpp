#include "Brain.hpp"
#include <iostream>

Brain::Brain() {
	for (int i = 0; i < 100; i++) {
		ideas[i] = "";
	}
	std::cout << "Brain Default constructor called" << std::endl;
}

Brain::Brain(const Brain& other) {
	for (int i = 0; i < 100; i++) {
		ideas[i] = other.ideas[i];
	}
	std::cout << "Brain Copy constructor called" << std::endl;
}

Brain& Brain::operator=(const Brain& other) {
	if (this != &other) {
		for (int i = 0; i < 100; i++) {
			ideas[i] = other.ideas[i];
		}
	}
	std::cout << "Brain Copy assignment operator called" << std::endl;
	return *this;
}

Brain::~Brain() {
	std::cout << "Brain Destructor called" << std::endl;
}

const std::string& Brain::getIdea(int index) const {
	return ideas[index];
}

void Brain::setIdea(int index, const std::string& idea) {
	ideas[index] = idea;
}
