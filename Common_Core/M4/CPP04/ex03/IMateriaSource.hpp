#ifndef IMATERIASOURCE_HPP
#define IMATERIASOURCE_HPP

#include <string>

class AMateria;

class IMateriaSource {
public:
	virtual ~IMateriaSource();
	virtual void learnMateria(AMateria*);
	virtual AMateria* createMateria(std::string const &type);
};

#endif
