#include "IMateriaSource.hpp"
#include "AMateria.hpp"

IMateriaSource::~IMateriaSource() {
}

void IMateriaSource::learnMateria(AMateria* m) {
	(void)m;
}

AMateria* IMateriaSource::createMateria(std::string const &type) {
	(void)type;
	return NULL;
}
