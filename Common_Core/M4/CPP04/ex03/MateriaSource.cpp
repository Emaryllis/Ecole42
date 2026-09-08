#include "MateriaSource.hpp"

#include <iostream>
#include <ostream>

#include "AMateria.hpp"

MateriaSource::MateriaSource() {
	for (int i = 0; i < 4; ++i)
		learned[i] = NULL;
	std::cout << "MateriaSource default constructor called" << std::endl;
}

MateriaSource::MateriaSource(MateriaSource const& other) {
	for (int i = 0; i < 4; ++i)
		learned[i] = NULL;
	copyLearned(other);
	std::cout << "MateriaSource copy constructor called" << std::endl;
}

MateriaSource& MateriaSource::operator=(MateriaSource const& other) {
	if (this != &other) {
		clearLearned();
		copyLearned(other);
	}
	std::cout << "MateriaSource copy assignment operator called" << std::endl;
	return *this;
}

MateriaSource::~MateriaSource() {
	clearLearned();
	std::cout << "MateriaSource destructor called" << std::endl;
}

void MateriaSource::learnMateria(AMateria* m) {
	if (!m)
		return;
	for (int i = 0; i < 4; ++i) {
		if (learned[i] == NULL) {
			learned[i] = m->clone();
			return;
		}
	}
}

AMateria* MateriaSource::createMateria(std::string const& type) {
	for (int i = 0; i < 4; ++i) {
		if (learned[i] && learned[i]->getType() == type)
			return learned[i]->clone();
	}
	return NULL;
}

void MateriaSource::clearLearned() {
	for (int i = 0; i < 4; ++i) {
		if (learned[i]) {
			delete learned[i];
			learned[i] = NULL;
		}
	}
}

void MateriaSource::copyLearned(MateriaSource const& other) {
	for (int i = 0; i < 4; ++i) {
		if (other.learned[i])
			learned[i] = other.learned[i]->clone();
		else
			learned[i] = NULL;
	}
}
