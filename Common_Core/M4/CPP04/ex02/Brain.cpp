#include "Brain.hpp"
#include <iostream>

Brain::Brain() {
	std::cout << "Brain Constructor called" << std::endl;
	for (int i = 0; i < 100; i++) {
		ideas[i] = "";
	}
}

Brain::Brain(const Brain& other) {
	std::cout << "Brain Copy Constructor called" << std::endl;
	for (int i = 0; i < 100; i++) {
		ideas[i] = other.ideas[i];
	}
}

Brain& Brain::operator=(const Brain& other) {
	std::cout << "Brain Copy Assignment operator called" << std::endl;
	if (this != &other) {
		for (int i = 0; i < 100; i++) {
			ideas[i] = other.ideas[i];
		}
	}
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
