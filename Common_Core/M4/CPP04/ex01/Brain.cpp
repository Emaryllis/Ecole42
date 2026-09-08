#include "Brain.hpp"
#include <iostream>

Brain::Brain() {
	for (int i = 0; i < 100; i++) {
		ideas[i] = "";
	}
	std::cout << "Brain default constructor called" << std::endl;
}

Brain::Brain(const Brain& other) {
	for (int i = 0; i < 100; i++) {
		ideas[i] = other.ideas[i];
	}
	std::cout << "Brain copy constructor called" << std::endl;
}

Brain& Brain::operator=(const Brain& other) {
	if (this != &other) {
		for (int i = 0; i < 100; i++) {
			ideas[i] = other.ideas[i];
		}
	}
	std::cout << "Brain copy assignment operator called" << std::endl;
	return *this;
}

Brain::~Brain() {
	std::cout << "Brain destructor called" << std::endl;
}

const std::string& Brain::getIdea(int index) const {
	return ideas[index];
}

void Brain::setIdea(int index, const std::string& idea) {
	ideas[index] = idea;
}
