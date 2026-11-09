#include "Character.hpp"
#include "Cure.hpp"
#include "Ice.hpp"
#include "MateriaSource.hpp"

int main() {
	MateriaSource *source = new MateriaSource();
	IMateriaSource *m_src = source;
	Ice *i_src = new Ice();
	m_src->learnMateria(i_src);
	delete i_src;

	Cure *c_src = new Cure();
	m_src->learnMateria(c_src);
	delete c_src;

	ICharacter *me = new Character("me");
	AMateria *tmp = m_src->createMateria("ice");
	me->equip(tmp);
	tmp = m_src->createMateria("cure");
	me->equip(tmp);

	ICharacter *bob = new Character("bob");
	me->use(0, *bob);
	me->use(1, *bob);
	delete me;
	delete bob;

	Character alice("alice");
	AMateria *saved = m_src->createMateria("ice");
	alice.equip(saved);
	Character aliceCopy(alice);
	alice.unequip(0);
	delete saved;
	aliceCopy.use(0, alice);

	MateriaSource sourceCopy(*source);
	delete m_src;

	const AMateria *extra = sourceCopy.createMateria("cure");
	delete extra;

	return 0;
}