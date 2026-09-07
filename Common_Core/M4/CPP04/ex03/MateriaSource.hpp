#ifndef MATERIASOURCE_HPP
#define MATERIASOURCE_HPP

#include <string>
#include "IMateriaSource.hpp"

class MateriaSource : public IMateriaSource {
public:
	MateriaSource();
	MateriaSource(MateriaSource const& other);
	MateriaSource& operator=(MateriaSource const& other);
	~MateriaSource();

	void learnMateria(AMateria* m);
	AMateria* createMateria(std::string const& type);
private:
	AMateria* learned[4];

	void clearLearned();
	void copyLearned(MateriaSource const& other);
};

#endif
