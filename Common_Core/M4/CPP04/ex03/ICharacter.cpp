#include "ICharacter.hpp"
#include "AMateria.hpp"

ICharacter::~ICharacter() {
}

std::string const& ICharacter::getName() const {
	static std::string empty = "";
	return empty;
}

void ICharacter::equip(AMateria* m) {
	(void)m;
}

void ICharacter::unequip(int idx) {
	(void)idx;
}

void ICharacter::use(int idx, ICharacter& target) {
	(void)idx;
	(void)target;
}
